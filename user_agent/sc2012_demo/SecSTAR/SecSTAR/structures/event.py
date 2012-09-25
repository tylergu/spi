"""
Represents temporal event
"""

class Event:
    """
    Args:
      
      type: event type
      time: event time
      host: source host (or current host)
      pid: source pid (or current pid)
    """
    def __init__(self, the_type, the_time, the_host, the_pid):
        self.type = the_type
        self.time = the_time
        self.host = the_host
        self.pid = the_pid

    def __str__(self):
        ret = 'Event = {'
        ret += 'type: %s, ' % self.type
        ret += 'time: %s, ' % self.time
        ret += 'host: %s, ' % self.host
        ret += 'pid: %s, ' % self.pid
        return ret

    def __cmp__(self, other):
        if other == None: return -1
        if self.time < other.time: return -1
        elif self.time == other.time: return 0
        else: return 1

    def pidhost(self):
        return "%s@%s" % (self.pid, self.host)
        

class ForkEvent(Event):
    def __init__(self, the_type, the_time, the_host, the_pid, the_child):
        Event.__init__(self, the_type, the_time, the_host, the_pid)
        self.child = the_child

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'child: %s}\n' % self.child
        return ret

    def child_pidhost(self):
        return "%s@%s" % (self.child, self.host)

class CloneEvent(Event):
    def __init__(self, the_type, the_time, the_host, the_pid, the_child):
        Event.__init__(self, the_type, the_time, the_host, the_pid)
        self.child = the_child

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'child: %s}\n' % self.child
        return ret

    def child_pidhost(self):
        return "%s@%s" % (self.child, self.host)

class ConnectEvent(Event):
    def __init__(self, the_type, the_time, src_host, src_pid, trg_host, trg_port):
        Event.__init__(self, the_type, the_time, src_host, src_pid)
        self.trg_host = trg_host
        self.trg_port = trg_port
        self.trg_pid = ''

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'trg_host: %s, trg_port: %s}\n' % (self.trg_host, self.trg_port)
        return ret

    def set_trg_pid(self, pid):
        self.trg_pid = pid

    def trg_pidhost(self):
        return "%s@%s" % (self.trg_pid, self.trg_host)

class AcceptEvent(Event):
    def __init__(self, the_type, the_time, src_host, src_pid, trg_host, trg_port):
        Event.__init__(self, the_type, the_time, src_host, src_pid)
        self.trg_host = trg_host
        self.trg_port = trg_port

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'trg_host: %s, trg_port: %s}\n' % (self.trg_host, self.trg_port)
        return ret

class ExitEvent(Event):
    def __init__(self, the_type, the_time, the_host, the_pid, exit_code):
        Event.__init__(self, the_type, the_time, the_host, the_pid)
        self.exit_code = exit_code

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'exit_code: %s}\n' % (self.exit_code)
        return ret

class SeteuidEvent(Event):
    def __init__(self, the_type, the_time, the_host, the_pid, new_euid):
        Event.__init__(self, the_type, the_time, the_host, the_pid)
        self.new_euid = new_euid

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'new_euid: %s}\n' % (self.new_euid)
        return ret
    
class ExeEvent(Event):
    def __init__(self, the_type, the_time, the_host, the_pid, new_exe):
        Event.__init__(self, the_type, the_time, the_host, the_pid)
        self.new_exe = new_exe

    def __str__(self):
        ret = Event.__str__(self)
        ret += 'new_exe: %s}\n' % (self.new_exe)
        return ret
