import subprocess
import sys
import os

def check_git_exists():
    try:
        # Check if Git is installed
        subprocess.call(["git", "--version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except OSError:
        return False
    return True

def install_git():
    if sys.version_info[0] == 2:
        version_cmd = subprocess.call
    else:
        version_cmd = subprocess.run

    # Install Git based on the operating system type
    system = sys.platform.lower()
    if "linux" in system:
        version_cmd(["sudo", "apt-get", "install", "git"])
    elif "darwin" in system:
        version_cmd(["brew", "install", "git"])
    elif "win" in system:
        print("Please manually install Git and ensure it is added to the system PATH.")
        sys.exit(1)

def check_file_changes(filepath):

    # Use Git to check the file status
    result = subprocess.Popen(["git", "status", "--porcelain", filepath], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, _ = result.communicate()

    # Return True if the file has changes
    return bool(out.decode('utf-8'))

def revert_to_original(filepath):
    # Use Git to revert the file to its original state
    subprocess.call(["git", "checkout", filepath])

def startup_check():
    file_path = os.getcwd() + "/ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c"
    python_executable = 'python' if sys.version_info[0] == 2 else 'python3'

    # Check if Git is installed, if not, try to install it
    if not check_git_exists():
        print("Git not detected, attempting to install...")
        install_git()

    # Check if Git is installed after the installation attempt
    if not check_git_exists():
        print("Git installation failed. Please manually install Git and add it to the system PATH.")
        sys.exit(1)

    # Check if the file has changes
    if check_file_changes(file_path):
        # If changes are detected, revert the file to its original state
        revert_to_original(file_path)
    # else:
    #     print "File {file_path} is unchanged."

if __name__ == "__main__":
    startup_check()
