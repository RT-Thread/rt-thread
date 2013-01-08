import os
import threading
import Queue

# Windows import 
import win32file
import win32pipe
import win32api
import win32con
import win32security
import win32process
import win32event

class Win32Spawn(object):
    def __init__(self, cmd, shell=False):
        self.queue = Queue.Queue()
        self.is_terminated = False
        self.wake_up_event = win32event.CreateEvent(None, 0, 0, None)
        
        exec_dir = os.getcwd()
        comspec = os.environ.get("COMSPEC", "cmd.exe")
        cmd = comspec + ' /c ' + cmd
        
        win32event.ResetEvent(self.wake_up_event)

        currproc = win32api.GetCurrentProcess()

        sa = win32security.SECURITY_ATTRIBUTES()
        sa.bInheritHandle = 1

        child_stdout_rd, child_stdout_wr = win32pipe.CreatePipe(sa, 0)
        child_stdout_rd_dup = win32api.DuplicateHandle(currproc, child_stdout_rd, currproc, 0, 0, win32con.DUPLICATE_SAME_ACCESS)
        win32file.CloseHandle(child_stdout_rd)

        child_stderr_rd, child_stderr_wr = win32pipe.CreatePipe(sa, 0)
        child_stderr_rd_dup = win32api.DuplicateHandle(currproc, child_stderr_rd, currproc, 0, 0, win32con.DUPLICATE_SAME_ACCESS)
        win32file.CloseHandle(child_stderr_rd)

        child_stdin_rd, child_stdin_wr = win32pipe.CreatePipe(sa, 0)
        child_stdin_wr_dup = win32api.DuplicateHandle(currproc, child_stdin_wr, currproc, 0, 0, win32con.DUPLICATE_SAME_ACCESS)
        win32file.CloseHandle(child_stdin_wr)

        startup_info = win32process.STARTUPINFO()
        startup_info.hStdInput = child_stdin_rd
        startup_info.hStdOutput = child_stdout_wr
        startup_info.hStdError = child_stderr_wr
        startup_info.dwFlags = win32process.STARTF_USESTDHANDLES

        cr_flags = 0
        cr_flags = win32process.CREATE_NEW_PROCESS_GROUP

        env = os.environ.copy()
        self.h_process, h_thread, dw_pid, dw_tid = win32process.CreateProcess(None, cmd, None, None, 1,
                                                                              cr_flags, env, os.path.abspath(exec_dir),
                                                                              startup_info)
 
        win32api.CloseHandle(h_thread)

        win32file.CloseHandle(child_stdin_rd)
        win32file.CloseHandle(child_stdout_wr)
        win32file.CloseHandle(child_stderr_wr)

        self.__child_stdout = child_stdout_rd_dup
        self.__child_stderr = child_stderr_rd_dup
        self.__child_stdin = child_stdin_wr_dup

        self.exit_code = -1

    def close(self):
        win32file.CloseHandle(self.__child_stdout)
        win32file.CloseHandle(self.__child_stderr)
        win32file.CloseHandle(self.__child_stdin)
        win32api.CloseHandle(self.h_process)
        win32api.CloseHandle(self.wake_up_event)

    def kill_subprocess():
        win32event.SetEvent(self.wake_up_event)

    def sleep(secs):
        win32event.ResetEvent(self.wake_up_event)
        timeout = int(1000 * secs)
        val = win32event.WaitForSingleObject(self.wake_up_event, timeout)
        if val == win32event.WAIT_TIMEOUT:
            return True
        else:
            # The wake_up_event must have been signalled
            return False
    
    def get(self, block=True, timeout=None):
        return self.queue.get(block=block, timeout=timeout)

    def qsize(self):
        return self.queue.qsize()

    def __wait_for_child(self):
        # kick off threads to read from stdout and stderr of the child process
        threading.Thread(target=self.__do_read, args=(self.__child_stdout, )).start()
        threading.Thread(target=self.__do_read, args=(self.__child_stderr, )).start()

        while True:
            # block waiting for the process to finish or the interrupt to happen
            handles = (self.wake_up_event, self.h_process)
            val = win32event.WaitForMultipleObjects(handles, 0, win32event.INFINITE)

            if val >= win32event.WAIT_OBJECT_0 and val < win32event.WAIT_OBJECT_0 + len(handles):
                handle = handles[val - win32event.WAIT_OBJECT_0]
                if handle == self.wake_up_event:
                    win32api.TerminateProcess(self.h_process, 1)
                    win32event.ResetEvent(self.wake_up_event)
                    return False
                elif handle == self.h_process:
                    # the process has ended naturally
                    return True
                else:
                    assert False, "Unknown handle fired"
            else:
                assert False, "Unexpected return from WaitForMultipleObjects"

    # Wait for job to finish. Since this method blocks, it can to be called from another thread.
    # If the application wants to kill the process, it should call kill_subprocess().
    def wait(self):
        if not self.__wait_for_child():
            # it's been killed
            result = False
        else:
            # normal termination
            self.exit_code = win32process.GetExitCodeProcess(self.h_process)
            result = self.exit_code == 0
        self.close()
        self.is_terminated = True
        
        return result

    # This method gets called on a worker thread to read from either a stderr
    # or stdout thread from the child process.
    def __do_read(self, handle):
        bytesToRead = 1024
        while 1:
            try:
                finished = 0
                hr, data = win32file.ReadFile(handle, bytesToRead, None)
                if data:
                    self.queue.put_nowait(data)
            except win32api.error:
                finished = 1

            if finished:
                return

    def start_pipe(self):
        def worker(pipe):
            return pipe.wait()
        
        thrd = threading.Thread(target=worker, args=(self, ))
        thrd.start()
