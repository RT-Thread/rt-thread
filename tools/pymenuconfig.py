# SPDX-License-Identifier: ISC
# -*- coding: utf-8 -*-

"""
Overview
========

pymenuconfig is a small and simple frontend to Kconfiglib that's written
entirely in Python using Tkinter as its GUI toolkit.

Motivation
==========

Kconfig is a nice and powerful framework for build-time configuration and lots
of projects already benefit from using it. Kconfiglib allows to utilize power of
Kconfig by using scripts written in pure Python, without requiring one to build
Linux kernel tools written in C (this can be quite tedious on anything that's
not *nix). The aim of this project is to implement simple and small Kconfiglib
GUI frontend that runs on as much systems as possible.

Tkinter GUI toolkit is a natural choice if portability is considered, as it's
a part of Python standard library and is available virtually in every CPython
installation.


User interface
==============

I've tried to replicate look and fill of Linux kernel 'menuconfig' tool that
many users are used to, including keyboard-oriented control and textual
representation of menus with fixed-width font.


Usage
=====

The pymenuconfig module is executable and parses command-line args, so the
most simple way to run menuconfig is to execute script directly:

  python pymenuconfig.py --kconfig Kconfig

As with most command-line tools list of options can be obtained with '--help':

  python pymenuconfig.py --help

If installed with setuptools, one can run it like this:

  python -m pymenuconfig --kconfig Kconfig

In case you're making a wrapper around menuconfig, you can either call main():

  import pymenuconfig
  pymenuconfig.main(['--kconfig', 'Kconfig'])

Or import MenuConfig class, instantiate it and manually run Tkinter's mainloop:

  import tkinter
  import kconfiglib
  from pymenuconfig import MenuConfig

  kconfig = kconfiglib.Kconfig()
  mconf = MenuConfig(kconfig)
  tkinter.mainloop()

"""

from __future__ import print_function

import os
import sys
import argparse
import kconfiglib

# Tk is imported differently depending on python major version
if sys.version_info[0] < 3:
    import Tkinter as tk
    import tkFont as font
    import tkFileDialog as filedialog
    import tkMessageBox as messagebox
else:
    import tkinter as tk
    from tkinter import font
    from tkinter import filedialog
    from tkinter import messagebox


class ListEntry(object):
    """
    Represents visible menu node and holds all information related to displaying
    menu node in a Listbox.

    Instances of this class also handle all interaction with main window.
    A node is displayed as a single line of text:
      PREFIX INDENT BODY POSTFIX
    - The PREFIX is always 3 characters or more and can take following values:
      '   ' comment, menu, bool choice, etc.
      Inside menus:
      '< >' bool symbol has value 'n'
      '<*>' bool symbol has value 'y'
      '[ ]' tristate symbol has value 'n'
      '[M]' tristate symbol has value 'm'
      '[*]' tristate symbol has value 'y'
      '- -' symbol has value 'n' that's not editable
      '-M-' symbol has value 'm' that's not editable
      '-*-' symbol has value 'y' that's not editable
      '(M)' tristate choice has value 'm'
      '(*)' tristate choice has value 'y'
      '(some value)' value of non-bool/tristate symbols
      Inside choices:
      '( )' symbol has value 'n'
      '(M)' symbol has value 'm'
      '(*)' symbol has value 'y'
    - INDENT is a sequence of space characters. It's used in implicit menus, and
      adds 2 spaces for each nesting level
    - BODY is a menu node prompt. '***' is added if node is a comment
    - POSTFIX adds '(NEW)', '--->' and selected choice symbol where applicable

    Attributes:

    node:
      MenuNode instance this ListEntry is created for.

    visible:
      Whether entry should be shown in main window.

    text:
      String to display in a main window's Listbox.

    refresh():
      Updates .visible and .text attribute values.

    set_tristate_value():
      Set value for bool/tristate symbols, value should be one of 0,1,2 or None.
      Usually it's called when user presses 'y', 'n', 'm' key.

    set_str_value():
      Set value for non-bool/tristate symbols, value is a string. Usually called
      with a value returned by one of MenuConfig.ask_for_* methods.

    toggle():
      Toggle bool/tristate symbol value. Called when '<Space>' key is pressed in
      a main window. Also selects choice value.

    select():
      Called when '<Return>' key is pressed in a main window with 'SELECT'
      action selected. Displays submenu, choice selection menu, or just selects
      choice value. For non-bool/tristate symbols asks MenuConfig window to
      handle value input via one of MenuConfig.ask_for_* methods.

    show_help():
      Called when '<Return>' key is pressed in a main window with 'HELP' action
      selected. Prepares text help and calls MenuConfig.show_text() to display
      text window.
    """

    # How to display value of BOOL and TRISTATE symbols
    TRI_TO_DISPLAY = {
        0: ' ',
        1: 'M',
        2: '*'
    }

    def __init__(self, mconf, node, indent):
        self.indent = indent
        self.node = node
        self.menuconfig = mconf
        self.visible = False
        self.text = None

    def __str__(self):
        return self.text

    def _is_visible(self):
        node = self.node
        v = True
        v = v and node.prompt is not None
        # It should be enough to check if prompt expression is not false and
        # for menu nodes whether 'visible if' is not false
        v = v and kconfiglib.expr_value(node.prompt[1]) > 0
        if node.item == kconfiglib.MENU:
            v = v and kconfiglib.expr_value(node.visibility) > 0
        # If node references Symbol, then we also account for symbol visibility
        # TODO: need to re-think whether this is needed
        if isinstance(node.item, kconfiglib.Symbol):
            if node.item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                v = v and len(node.item.assignable) > 0
            else:
                v = v and node.item.visibility > 0
        return v

    def _get_text(self):
        """
        Compute textual representation of menu node (a line in ListView)
        """
        node = self.node
        item = node.item
        # Determine prefix
        prefix = '   '
        if (isinstance(item, kconfiglib.Symbol) and item.choice is None or
            isinstance(item, kconfiglib.Choice) and item.type is kconfiglib.TRISTATE):
            # The node is for either a symbol outside of choice statement
            # or a tristate choice
            if item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                value = ListEntry.TRI_TO_DISPLAY[item.tri_value]
                if len(item.assignable) > 1:
                    # Symbol is editable
                    if 1 in item.assignable:
                        prefix = '<{}>'.format(value)
                    else:
                        prefix = '[{}]'.format(value)
                else:
                    # Symbol is not editable
                    prefix = '-{}-'.format(value)
            else:
                prefix = '({})'.format(item.str_value)
        elif isinstance(item, kconfiglib.Symbol) and item.choice is not None:
            # The node is for symbol inside choice statement
            if item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                value = ListEntry.TRI_TO_DISPLAY[item.tri_value]
                if len(item.assignable) > 0:
                    # Symbol is editable
                    prefix = '({})'.format(value)
                else:
                    # Symbol is not editable
                    prefix = '-{}-'.format(value)
            else:
                prefix = '({})'.format(item.str_value)

        # Prefix should be at least 3 chars long
        if len(prefix) < 3:
            prefix += ' ' * (3 - len(prefix))
        # Body
        body = ''
        if node.prompt is not None:
            if item is kconfiglib.COMMENT:
                body = '*** {} ***'.format(node.prompt[0])
            else:
                body = node.prompt[0]
        # Suffix
        is_menu = False
        is_new = False
        if (item is kconfiglib.MENU
            or isinstance(item, kconfiglib.Symbol) and node.is_menuconfig
            or isinstance(item, kconfiglib.Choice)):
            is_menu = True
        if isinstance(item, kconfiglib.Symbol) and item.user_value is None:
            is_new = True
        # For symbol inside choice that has 'y' value, '(NEW)' is not displayed
        if (isinstance(item, kconfiglib.Symbol)
            and item.choice and item.choice.tri_value == 2):
            is_new = False
        # Choice selection - displayed only for choices which have 'y' value
        choice_selection = None
        if isinstance(item, kconfiglib.Choice) and node.item.str_value == 'y':
            choice_selection = ''
            if item.selection is not None:
                sym = item.selection
                if sym.nodes and sym.nodes[0].prompt is not None:
                    choice_selection = sym.nodes[0].prompt[0]
        text = '  {prefix} {indent}{body}{choice}{new}{menu}'.format(
            prefix=prefix,
            indent='  ' * self.indent,
            body=body,
            choice='' if choice_selection is None else ' ({})'.format(
                choice_selection
            ),
            new=' (NEW)' if is_new else '',
            menu=' --->' if is_menu else ''
        )
        return text

    def refresh(self):
        self.visible = self._is_visible()
        self.text = self._get_text()

    def set_tristate_value(self, value):
        """
        Call to change value of BOOL, TRISTATE symbols

        It's preferred to use this instead of item.set_value as it handles
        all necessary interaction with MenuConfig window when symbol value
        changes

        None value is accepted but ignored
        """
        item = self.node.item
        if (isinstance(item, (kconfiglib.Symbol, kconfiglib.Choice))
            and item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE)
            and value is not None):
            if value in item.assignable:
                item.set_value(value)
            elif value == 2 and 1 in item.assignable:
                print(
                    'Symbol {} value is limited to \'m\'. Setting value \'m\' instead of \'y\''.format(item.name),
                    file=sys.stderr
                )
                item.set_value(1)
            self.menuconfig.mark_as_changed()
            self.menuconfig.refresh_display()

    def set_str_value(self, value):
        """
        Call to change value of HEX, INT, STRING symbols

        It's preferred to use this instead of item.set_value as it handles
        all necessary interaction with MenuConfig window when symbol value
        changes

        None value is accepted but ignored
        """
        item = self.node.item
        if (isinstance(item, kconfiglib.Symbol)
            and item.type in (kconfiglib.INT, kconfiglib.HEX, kconfiglib.STRING)
            and value is not None):
            item.set_value(value)
            self.menuconfig.mark_as_changed()
            self.menuconfig.refresh_display()

    def toggle(self):
        """
        Called when <space> key is pressed
        """
        item = self.node.item
        if (isinstance(item, (kconfiglib.Symbol, kconfiglib.Choice))
            and item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE)):
            value = item.tri_value
            # Find next value in Symbol/Choice.assignable, or use assignable[0]
            try:
                it = iter(item.assignable)
                while value != next(it):
                    pass
                self.set_tristate_value(next(it))
            except StopIteration:
                self.set_tristate_value(item.assignable[0])

    def select(self):
        """
        Called when <Return> key is pressed and SELECT action is selected
        """
        item = self.node.item
        # - Menu: dive into submenu
        # - INT, HEX, STRING symbol: raise prompt to enter symbol value
        # - BOOL, TRISTATE symbol inside 'y'-valued Choice: set 'y' value
        if (item is kconfiglib.MENU
            or isinstance(item, kconfiglib.Symbol) and self.node.is_menuconfig
            or isinstance(item, kconfiglib.Choice)):
            # Dive into submenu
            self.menuconfig.show_submenu(self.node)
        elif (isinstance(item, kconfiglib.Symbol) and item.type in
              (kconfiglib.INT, kconfiglib.HEX, kconfiglib.STRING)):
            # Raise prompt to enter symbol value
            ident = self.node.prompt[0] if self.node.prompt is not None else None
            title = 'Symbol: {}'.format(item.name)
            if item.type is kconfiglib.INT:
                # Find enabled ranges
                ranges = [
                    (int(start.str_value), int(end.str_value))
                    for start, end, expr in item.ranges
                    if kconfiglib.expr_value(expr) > 0
                ]
                # Raise prompt
                self.set_str_value(str(self.menuconfig.ask_for_int(
                    ident=ident,
                    title=title,
                    value=item.str_value,
                    ranges=ranges
                )))
            elif item.type is kconfiglib.HEX:
                # Find enabled ranges
                ranges = [
                    (int(start.str_value, base=16), int(end.str_value, base=16))
                    for start, end, expr in item.ranges
                    if kconfiglib.expr_value(expr) > 0
                ]
                # Raise prompt
                self.set_str_value(hex(self.menuconfig.ask_for_hex(
                    ident=ident,
                    title=title,
                    value=item.str_value,
                    ranges=ranges
                )))
            elif item.type is kconfiglib.STRING:
                # Raise prompt
                self.set_str_value(self.menuconfig.ask_for_string(
                    ident=ident,
                    title=title,
                    value=item.str_value
                ))
        elif (isinstance(item, kconfiglib.Symbol)
              and item.choice is not None and item.choice.tri_value == 2):
            # Symbol inside choice -> set symbol value to 'y'
            self.set_tristate_value(2)

    def show_help(self):
        node = self.node
        item = self.node.item
        if isinstance(item, (kconfiglib.Symbol, kconfiglib.Choice)):
            title = 'Help for symbol: {}'.format(item.name)
            if node.help:
                help = node.help
            else:
                help = 'There is no help available for this option.\n'
            lines = []
            lines.append(help)
            lines.append(
                'Symbol: {} [={}]'.format(
                    item.name if item.name else '<UNNAMED>', item.str_value
                )
            )
            lines.append('Type  : {}'.format(kconfiglib.TYPE_TO_STR[item.type]))
            for n in item.nodes:
                lines.append('Prompt: {}'.format(n.prompt[0] if n.prompt else '<EMPTY>'))
                lines.append('  Defined at {}:{}'.format(n.filename, n.linenr))
                lines.append('  Depends on: {}'.format(kconfiglib.expr_str(n.dep)))
            text = '\n'.join(lines)
        else:
            title = 'Help'
            text = 'Help not available for this menu node.\n'
        self.menuconfig.show_text(text, title)
        self.menuconfig.refresh_display()


class EntryDialog(object):
    """
    Creates modal dialog (top-level Tk window) with labels, entry box and two
    buttons: OK and CANCEL.
    """
    def __init__(self, master, text, title, ident=None, value=None):
        self.master = master
        dlg = self.dlg = tk.Toplevel(master)
        self.dlg.withdraw() #hiden window
        dlg.title(title)
        # Identifier label
        if ident is not None:
            self.label_id = tk.Label(dlg, anchor=tk.W, justify=tk.LEFT)
            self.label_id['font'] = font.nametofont('TkFixedFont')
            self.label_id['text'] = '# {}'.format(ident)
            self.label_id.pack(fill=tk.X, padx=2, pady=2)
        # Label
        self.label = tk.Label(dlg, anchor=tk.W, justify=tk.LEFT)
        self.label['font'] = font.nametofont('TkFixedFont')
        self.label['text'] = text
        self.label.pack(fill=tk.X, padx=10, pady=4)
        # Entry box
        self.entry = tk.Entry(dlg)
        self.entry['font'] = font.nametofont('TkFixedFont')
        self.entry.pack(fill=tk.X, padx=2, pady=2)
        # Frame for buttons
        self.frame = tk.Frame(dlg)
        self.frame.pack(padx=2, pady=2)
        # Button
        self.btn_accept = tk.Button(self.frame, text='< Ok >', command=self.accept)
        self.btn_accept['font'] = font.nametofont('TkFixedFont')
        self.btn_accept.pack(side=tk.LEFT, padx=2)
        self.btn_cancel = tk.Button(self.frame, text='< Cancel >', command=self.cancel)
        self.btn_cancel['font'] = font.nametofont('TkFixedFont')
        self.btn_cancel.pack(side=tk.LEFT, padx=2)
        # Bind Enter and Esc keys
        self.dlg.bind('<Return>', self.accept)
        self.dlg.bind('<Escape>', self.cancel)
        # Dialog is resizable only by width
        self.dlg.resizable(1, 0)
        # Set supplied value (if any)
        if value is not None:
            self.entry.insert(0, value)
            self.entry.selection_range(0, tk.END)
        # By default returned value is None. To caller this means that entry
        # process was cancelled
        self.value = None
        # Modal dialog
        dlg.transient(master)
        dlg.grab_set()
        # Center dialog window
        _center_window_above_parent(master, dlg)
        self.dlg.deiconify() # show window
        # Focus entry field
        self.entry.focus_set()

    def accept(self, ev=None):
        self.value = self.entry.get()
        self.dlg.destroy()

    def cancel(self, ev=None):
        self.dlg.destroy()


class TextDialog(object):
    def __init__(self, master, text, title):
        self.master = master
        dlg = self.dlg = tk.Toplevel(master)
        self.dlg.withdraw() #hiden window
        dlg.title(title)
        dlg.minsize(600,400)
        # Text
        self.text = tk.Text(dlg, height=1)
        self.text['font'] = font.nametofont('TkFixedFont')
        self.text.insert(tk.END, text)
        # Make text read-only
        self.text['state'] = tk.DISABLED
        self.text.pack(fill=tk.BOTH, expand=1, padx=4, pady=4)
        # Frame for buttons
        self.frame = tk.Frame(dlg)
        self.frame.pack(padx=2, pady=2)
        # Button
        self.btn_accept = tk.Button(self.frame, text='< Ok >', command=self.accept)
        self.btn_accept['font'] = font.nametofont('TkFixedFont')
        self.btn_accept.pack(side=tk.LEFT, padx=2)
        # Bind Enter and Esc keys
        self.dlg.bind('<Return>', self.accept)
        self.dlg.bind('<Escape>', self.cancel)
        # Modal dialog
        dlg.transient(master)
        dlg.grab_set()
        # Center dialog window
        _center_window_above_parent(master, dlg)
        self.dlg.deiconify() # show window
        # Focus entry field
        self.text.focus_set()

    def accept(self, ev=None):
        self.dlg.destroy()

    def cancel(self, ev=None):
        self.dlg.destroy()


class MenuConfig(object):
    (
        ACTION_SELECT,
        ACTION_EXIT,
        ACTION_HELP,
        ACTION_LOAD,
        ACTION_SAVE,
        ACTION_SAVE_AS
    ) = range(6)

    ACTIONS = (
        ('Select', ACTION_SELECT),
        ('Exit', ACTION_EXIT),
        ('Help', ACTION_HELP),
        ('Load', ACTION_LOAD),
        ('Save', ACTION_SAVE),
        ('Save as', ACTION_SAVE_AS),
    )

    def __init__(self, kconfig, __silent=None):
        self.kconfig = kconfig
        self.__silent = __silent
        if self.__silent is True:
            return

        # Instantiate Tk widgets
        self.root = tk.Tk()
        self.root.withdraw() #hiden window
        dlg = self.root

        # Window title
        dlg.title('pymenuconfig')
        # Some empirical window size
        dlg.minsize(500, 300)
        dlg.geometry('800x600')

        # Label that shows position in menu tree
        self.label_position = tk.Label(
            dlg,
            anchor=tk.W,
            justify=tk.LEFT,
            font=font.nametofont('TkFixedFont')
        )
        self.label_position.pack(fill=tk.X, padx=2)

        # 'Tip' frame and text
        self.frame_tip = tk.LabelFrame(
            dlg,
            text='Tip'
        )
        self.label_tip = tk.Label(
            self.frame_tip,
            anchor=tk.W,
            justify=tk.LEFT,
            font=font.nametofont('TkFixedFont')
        )
        self.label_tip['text'] = '\n'.join([
            'Arrow keys navigate the menu. <Enter> performs selected operation (set of buttons at the bottom)',
            'Pressing <Y> includes, <N> excludes, <M> modularizes features',
            'Press <Esc> to go one level up. Press <Esc> at top level to exit',
            'Legend: [*] built-in  [ ] excluded  <M> module  < > module capable'
        ])
        self.label_tip.pack(fill=tk.BOTH, expand=1, padx=4, pady=4)
        self.frame_tip.pack(fill=tk.X, padx=2)

        # Main ListBox where all the magic happens
        self.list = tk.Listbox(
            dlg,
            selectmode=tk.SINGLE,
            activestyle=tk.NONE,
            font=font.nametofont('TkFixedFont'),
            height=1,
        )
        self.list['foreground'] = 'Blue'
        self.list['background'] = 'Gray95'
        # Make selection invisible
        self.list['selectbackground'] = self.list['background']
        self.list['selectforeground'] = self.list['foreground']
        self.list.pack(fill=tk.BOTH, expand=1, padx=20, ipadx=2)

        # Frame with radio buttons
        self.frame_radio = tk.Frame(dlg)
        self.radio_buttons = []
        self.tk_selected_action = tk.IntVar()
        for text, value in MenuConfig.ACTIONS:
            btn = tk.Radiobutton(
                self.frame_radio,
                variable=self.tk_selected_action,
                value=value
            )
            btn['text'] = '< {} >'.format(text)
            btn['font'] = font.nametofont('TkFixedFont')
            btn['indicatoron'] = 0
            btn.pack(side=tk.LEFT)
            self.radio_buttons.append(btn)
        self.frame_radio.pack(anchor=tk.CENTER, pady=4)
        # Label with status information
        self.tk_status = tk.StringVar()
        self.label_status = tk.Label(
            dlg,
            textvariable=self.tk_status,
            anchor=tk.W,
            justify=tk.LEFT,
            font=font.nametofont('TkFixedFont')
        )
        self.label_status.pack(fill=tk.X, padx=4, pady=4)
        # Center window
        _center_window(self.root, dlg)
        self.root.deiconify() # show window
        # Disable keyboard focus on all widgets ...
        self._set_option_to_all_children(dlg, 'takefocus', 0)
        # ... except for main ListBox
        self.list['takefocus'] = 1
        self.list.focus_set()
        # Bind keys
        dlg.bind('<Escape>', self.handle_keypress)
        dlg.bind('<space>', self.handle_keypress)
        dlg.bind('<Return>', self.handle_keypress)
        dlg.bind('<Right>', self.handle_keypress)
        dlg.bind('<Left>', self.handle_keypress)
        dlg.bind('<Up>', self.handle_keypress)
        dlg.bind('<Down>', self.handle_keypress)
        dlg.bind('n', self.handle_keypress)
        dlg.bind('m', self.handle_keypress)
        dlg.bind('y', self.handle_keypress)
        # Register callback that's called when window closes
        dlg.wm_protocol('WM_DELETE_WINDOW', self._close_window)
        # Init fields
        self.node = None
        self.node_stack = []
        self.all_entries = []
        self.shown_entries = []
        self.config_path = None
        self.unsaved_changes = False
        self.status_string = 'NEW CONFIG'
        self.update_status()
        # Display first child of top level node (the top level node is 'mainmenu')
        self.show_node(self.kconfig.top_node)

    def _set_option_to_all_children(self, widget, option, value):
        widget[option] = value
        for n,c in widget.children.items():
            self._set_option_to_all_children(c, option, value)

    def _invert_colors(self, idx):
        self.list.itemconfig(idx, {'bg' : self.list['foreground']})
        self.list.itemconfig(idx, {'fg' : self.list['background']})

    @property
    def _selected_entry(self):
        # type: (...) -> ListEntry
        active_idx = self.list.index(tk.ACTIVE)
        if active_idx >= 0 and active_idx < len(self.shown_entries):
            return self.shown_entries[active_idx]
        return None

    def _select_node(self, node):
        # type: (kconfiglib.MenuNode) -> None
        """
        Attempts to select entry that corresponds to given MenuNode in main listbox
        """
        idx = None
        for i, e in enumerate(self.shown_entries):
            if e.node is node:
                idx = i
                break
        if idx is not None:
            self.list.activate(idx)
            self.list.see(idx)
            self._invert_colors(idx)

    def handle_keypress(self, ev):
        keysym = ev.keysym
        if keysym == 'Left':
            self._select_action(prev=True)
        elif keysym == 'Right':
            self._select_action(prev=False)
        elif keysym == 'Up':
            self.refresh_display(reset_selection=False)
        elif keysym == 'Down':
            self.refresh_display(reset_selection=False)
        elif keysym == 'space':
            self._selected_entry.toggle()
        elif keysym in ('n', 'm', 'y'):
            self._selected_entry.set_tristate_value(kconfiglib.STR_TO_TRI[keysym])
        elif keysym == 'Return':
            action = self.tk_selected_action.get()
            if action == self.ACTION_SELECT:
                self._selected_entry.select()
            elif action == self.ACTION_EXIT:
                self._action_exit()
            elif action == self.ACTION_HELP:
                self._selected_entry.show_help()
            elif action == self.ACTION_LOAD:
                if self.prevent_losing_changes():
                    self.open_config()
            elif action == self.ACTION_SAVE:
                self.save_config()
            elif action == self.ACTION_SAVE_AS:
                self.save_config(force_file_dialog=True)
        elif keysym == 'Escape':
            self._action_exit()
        pass

    def _close_window(self):
        if self.prevent_losing_changes():
            print('Exiting..')
            if self.__silent is True:
                return
            self.root.destroy()

    def _action_exit(self):
        if self.node_stack:
            self.show_parent()
        else:
            self._close_window()

    def _select_action(self, prev=False):
        # Determine the radio button that's activated
        action = self.tk_selected_action.get()
        if prev:
            action -= 1
        else:
            action += 1
        action %= len(MenuConfig.ACTIONS)
        self.tk_selected_action.set(action)

    def _collect_list_entries(self, start_node, indent=0):
        """
        Given first MenuNode of nodes list at some level in menu hierarchy,
        collects nodes that may be displayed when viewing and editing that
        hierarchy level. Includes implicit menu nodes, i.e. the ones dependent
        on 'config' entry via 'if' statement which are internally represented
        as children of their dependency
        """
        entries = []
        n = start_node
        while n is not None:
            entries.append(ListEntry(self, n, indent))
            # If node refers to a symbol (X) and has children, it is either
            # 'config' or 'menuconfig'. The children are items inside 'if X'
            # block that immediately follows 'config' or 'menuconfig' entry.
            # If it's a 'menuconfig' then corresponding MenuNode is shown as a
            # regular menu entry. But if it's a 'config', then its children need
            # to be shown in the same list with their texts indented
            if (n.list is not None
                and isinstance(n.item, kconfiglib.Symbol)
                and n.is_menuconfig == False):
                entries.extend(
                    self._collect_list_entries(n.list, indent=indent + 1)
                )
            n = n.next
        return entries

    def refresh_display(self, reset_selection=False):
        # Refresh list entries' attributes
        for e in self.all_entries:
            e.refresh()
        # Try to preserve selection upon refresh
        selected_entry = self._selected_entry
        # Also try to preserve listbox scroll offset
        # If not preserved, the see() method will make wanted item to appear
        # at the bottom of the list, even if previously it was in center
        scroll_offset = self.list.yview()[0]
        # Show only visible entries
        self.shown_entries = [e for e in self.all_entries if e.visible]
        # Refresh listbox contents
        self.list.delete(0, tk.END)
        self.list.insert(0, *self.shown_entries)
        if selected_entry and not reset_selection:
            # Restore scroll position
            self.list.yview_moveto(scroll_offset)
            # Activate previously selected node
            self._select_node(selected_entry.node)
        else:
            # Select the topmost entry
            self.list.activate(0)
            self._invert_colors(0)
        # Select ACTION_SELECT on each refresh (mimic C menuconfig)
        self.tk_selected_action.set(self.ACTION_SELECT)
        # Display current location in configuration tree
        pos = []
        for n in self.node_stack + [self.node]:
            pos.append(n.prompt[0] if n.prompt else '[none]')
        self.label_position['text'] = u'# ' + u' -> '.join(pos)

    def show_node(self, node):
        self.node = node
        if node.list is not None:
            self.all_entries = self._collect_list_entries(node.list)
        else:
            self.all_entries = []
        self.refresh_display(reset_selection=True)

    def show_submenu(self, node):
        self.node_stack.append(self.node)
        self.show_node(node)

    def show_parent(self):
        if self.node_stack:
            select_node = self.node
            parent_node = self.node_stack.pop()
            self.show_node(parent_node)
            # Restore previous selection
            self._select_node(select_node)
            self.refresh_display(reset_selection=False)

    def ask_for_string(self, ident=None, title='Enter string', value=None):
        """
        Raises dialog with text entry widget and asks user to enter string

        Return:
            - str - user entered string
            - None - entry was cancelled
        """
        text = 'Please enter a string value\n' \
               'User <Enter> key to accept the value\n' \
               'Use <Esc> key to cancel entry\n'
        d = EntryDialog(self.root, text, title, ident=ident, value=value)
        self.root.wait_window(d.dlg)
        self.list.focus_set()
        return d.value

    def ask_for_int(self, ident=None, title='Enter integer value', value=None, ranges=()):
        """
        Raises dialog with text entry widget and asks user to enter decimal number
        Ranges should be iterable of tuples (start, end),
        where 'start' and 'end' specify allowed value range (inclusively)

        Return:
            - int - when valid number that falls within any one of specified ranges is entered
            - None - invalid number or entry was cancelled
        """
        text = 'Please enter a decimal value. Fractions will not be accepted\n' \
               'User <Enter> key to accept the value\n' \
               'Use <Esc> key to cancel entry\n'
        d = EntryDialog(self.root, text, title, ident=ident, value=value)
        self.root.wait_window(d.dlg)
        self.list.focus_set()
        ivalue = None
        if d.value:
            try:
                ivalue = int(d.value)
            except ValueError:
                messagebox.showerror('Bad value', 'Entered value \'{}\' is not an integer'.format(d.value))
            if ivalue is not None and ranges:
                allowed = False
                for start, end in ranges:
                    allowed = allowed or start <= ivalue and ivalue <= end
                if not allowed:
                    messagebox.showerror(
                        'Bad value',
                        'Entered value \'{:d}\' is out of range\n'
                        'Allowed:\n{}'.format(
                            ivalue,
                            '\n'.join(['  {:d} - {:d}'.format(s,e) for s,e in ranges])
                        )
                    )
                    ivalue = None
        return ivalue

    def ask_for_hex(self, ident=None, title='Enter hexadecimal value', value=None, ranges=()):
        """
        Raises dialog with text entry widget and asks user to enter decimal number
        Ranges should be iterable of tuples (start, end),
        where 'start' and 'end' specify allowed value range (inclusively)

        Return:
            - int - when valid number that falls within any one of specified ranges is entered
            - None - invalid number or entry was cancelled
        """
        text = 'Please enter a hexadecimal value\n' \
               'User <Enter> key to accept the value\n' \
               'Use <Esc> key to cancel entry\n'
        d = EntryDialog(self.root, text, title, ident=ident, value=value)
        self.root.wait_window(d.dlg)
        self.list.focus_set()
        hvalue = None
        if d.value:
            try:
                hvalue = int(d.value, base=16)
            except ValueError:
                messagebox.showerror('Bad value', 'Entered value \'{}\' is not a hexadecimal value'.format(d.value))
            if hvalue is not None and ranges:
                allowed = False
                for start, end in ranges:
                    allowed = allowed or start <= hvalue and hvalue <= end
                if not allowed:
                    messagebox.showerror(
                        'Bad value',
                        'Entered value \'0x{:x}\' is out of range\n'
                        'Allowed:\n{}'.format(
                            hvalue,
                            '\n'.join(['  0x{:x} - 0x{:x}'.format(s,e) for s,e in ranges])
                        )
                    )
                    hvalue = None
        return hvalue

    def show_text(self, text, title='Info'):
        """
        Raises dialog with read-only text view that contains supplied text
        """
        d = TextDialog(self.root, text, title)
        self.root.wait_window(d.dlg)
        self.list.focus_set()

    def mark_as_changed(self):
        """
        Marks current config as having unsaved changes
        Should be called whenever config value is changed
        """
        self.unsaved_changes = True
        self.update_status()

    def set_status_string(self, status):
        """
        Sets status string displayed at the bottom of the window
        """
        self.status_string = status
        self.update_status()

    def update_status(self):
        """
        Updates status bar display
        Status bar displays:
        - unsaved status
        - current config path
        - status string (see set_status_string())
        """
        if self.__silent is True:
            return
        self.tk_status.set('{} [{}] {}'.format(
            '<UNSAVED>' if self.unsaved_changes else '',
            self.config_path if self.config_path else '',
            self.status_string
        ))

    def _check_is_visible(self, node):
        v = True
        v = v and node.prompt is not None
        # It should be enough to check if prompt expression is not false and
        # for menu nodes whether 'visible if' is not false
        v = v and kconfiglib.expr_value(node.prompt[1]) > 0
        if node.item == kconfiglib.MENU:
            v = v and kconfiglib.expr_value(node.visibility) > 0
        # If node references Symbol, then we also account for symbol visibility
        # TODO: need to re-think whether this is needed
        if isinstance(node.item, kconfiglib.Symbol):
            if node.item.type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                v = v and len(node.item.assignable) > 0
            else:
                v = v and node.item.visibility > 0
        return v

    def config_is_changed(self):
        is_changed = False
        node = self.kconfig.top_node.list
        if not node:
            # Empty configuration
            return is_changed

        while 1:
            item = node.item
            if isinstance(item, kconfiglib.Symbol) and item.user_value is None and self._check_is_visible(node):
                is_changed = True
                print("Config \"# {}\" has changed, need save config file\n".format(node.prompt[0]))
                break;

            # Iterative tree walk using parent pointers

            if node.list:
                node = node.list
            elif node.next:
                node = node.next
            else:
                while node.parent:
                    node = node.parent
                    if node.next:
                        node = node.next
                        break
                else:
                    break
        return is_changed

    def prevent_losing_changes(self):
        """
        Checks if there are unsaved changes and asks user to save or discard them
        This routine should be called whenever current config is going to be discarded

        Raises the usual 'Yes', 'No', 'Cancel' prompt.

        Return:
            - True: caller may safely drop current config state
            - False: user needs to continue work on current config ('Cancel' pressed or saving failed)
        """
        if self.config_is_changed() == True:
            self.mark_as_changed()
        if not self.unsaved_changes:
            return True
        
        if self.__silent:
            saved = self.save_config()
            return saved
        res = messagebox.askyesnocancel(
            parent=self.root,
            title='Unsaved changes',
            message='Config has unsaved changes. Do you want to save them?'
        )
        if res is None:
            return False
        elif res is False:
            return True
        # Otherwise attempt to save config and succeed only if config has been saved successfully
        saved = self.save_config()
        return saved

    def open_config(self, path=None):
        if path is None:
            # Create open dialog. Either existing file is selected or no file is selected as a result
            path = filedialog.askopenfilename(
                parent=self.root,
                title='Open config..',
                initialdir=os.path.dirname(self.config_path) if self.config_path else os.getcwd(),
                filetypes=(('.config files', '*.config'), ('All files', '*.*'))
            )
            if not path or not os.path.isfile(path):
                return False
        path = os.path.abspath(path)
        print('Loading config: \'{}\''.format(path))
        # Try to open given path
        # If path does not exist, we still set current config path to it but don't load anything
        self.unsaved_changes = False
        self.config_path = path
        if not os.path.exists(path):
            self.set_status_string('New config')
            self.mark_as_changed()
            return True
        # Load config and set status accordingly
        try:
            self.kconfig.load_config(path)
        except IOError as e:
            self.set_status_string('Failed to load: \'{}\''.format(path))
            if not self.__silent:
                self.refresh_display()
            print('Failed to load config \'{}\': {}'.format(path, e))
            return False
        self.set_status_string('Opened config')
        if not self.__silent:
            self.refresh_display()
        return True

    def save_config(self, force_file_dialog=False):
        path = self.config_path
        if path is None or force_file_dialog:
            path = filedialog.asksaveasfilename(
                parent=self.root,
                title='Save config as..',
                initialdir=os.path.dirname(self.config_path) if self.config_path else os.getcwd(),
                initialfile=os.path.basename(self.config_path) if self.config_path else None,
                defaultextension='.config',
                filetypes=(('.config files', '*.config'), ('All files', '*.*'))
            )
        if not path:
            return False
        path = os.path.abspath(path)
        print('Saving config: \'{}\''.format(path))
        # Try to save config to selected path
        try:
            self.kconfig.write_config(path, header="#\n# Automatically generated file; DO NOT EDIT.\n")
            self.unsaved_changes = False
            self.config_path = path
            self.set_status_string('Saved config')
        except IOError as e:
            self.set_status_string('Failed to save: \'{}\''.format(path))
            print('Save failed: {}'.format(e), file=sys.stderr)
            return False
        return True


def _center_window(root, window):
    # type: (tk.Tk, tk.Toplevel) -> None
    """
    Attempts to center window on screen
    """
    root.update_idletasks()
    # root.eval('tk::PlaceWindow {!s} center'.format(
    #     window.winfo_pathname(window.winfo_id())
    # ))
    w = window.winfo_width()
    h = window.winfo_height()
    ws = window.winfo_screenwidth()
    hs = window.winfo_screenheight()
    x = (ws / 2) - (w / 2)
    y = (hs / 2) - (h / 2)
    window.geometry('+{:d}+{:d}'.format(int(x), int(y)))
    window.lift()
    window.focus_force()


def _center_window_above_parent(root, window):
    # type: (tk.Tk, tk.Toplevel) -> None
    """
    Attempts to center window above its parent window
    """
    # root.eval('tk::PlaceWindow {!s} center'.format(
    #     window.winfo_pathname(window.winfo_id())
    # ))
    root.update_idletasks()
    parent = window.master
    w = window.winfo_width()
    h = window.winfo_height()
    px = parent.winfo_rootx()
    py = parent.winfo_rooty()
    pw = parent.winfo_width()
    ph = parent.winfo_height()
    x = px + (pw / 2) - (w / 2)
    y = py + (ph / 2) - (h / 2)
    window.geometry('+{:d}+{:d}'.format(int(x), int(y)))
    window.lift()
    window.focus_force()


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    # Instantiate cmd options parser
    parser = argparse.ArgumentParser(
        description='Interactive Kconfig configuration editor'
    )
    parser.add_argument(
        '--kconfig',
        metavar='FILE',
        type=str,
        default='Kconfig',
        help='path to root Kconfig file'
    )
    parser.add_argument(
        '--config',
        metavar='FILE',
        type=str,
        help='path to .config file to load'
    )
    if "--silent" in argv:
        parser.add_argument(
            '--silent',
            dest = '_silent_',
            type=str,
            help='silent mode, not show window'
        )
    args = parser.parse_args(argv)
    kconfig_path = args.kconfig
    config_path = args.config
    # Verify that Kconfig file exists
    if not os.path.isfile(kconfig_path):
        raise RuntimeError('\'{}\': no such file'.format(kconfig_path))

    # Parse Kconfig files
    kconf = kconfiglib.Kconfig(filename=kconfig_path)

    if "--silent" not in argv:
        print("In normal mode. Will show menuconfig window.")
        mc = MenuConfig(kconf)
        # If config file was specified, load it
        if config_path:
            mc.open_config(config_path)

        print("Enter mainloop. Waiting...")
        tk.mainloop()
    else:
        print("In silent mode. Don`t show menuconfig window.")
        mc = MenuConfig(kconf, True)
        # If config file was specified, load it
        if config_path:
            mc.open_config(config_path)
        mc._close_window()


if __name__ == '__main__':
    main()
