import socket


def dump_recv(sock):
    try:
        x = sock.recv(4096)
    except socket.timeout, err:
        print(err.args[0])
        return
    print(' '.join(str(ord(str(c))) for c in reversed(list(x))))


def loop_dump_recv(sock):
    has_received = False
    try:
        while True:
            x = sock.recv(4096)
            has_received = True
            print(' '.join(str(ord(str(c))) for c in reversed(list(x))))

    except socket.timeout, err:
        if not has_received:
            print(err.args[0])
        return


def dump_data(x):
    print('---DATA---')
    print(' '.join(str(ord(str(c))) for c in reversed(list(x))))


try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(1)
    s.connect(("10.10.253.144", 42142))

    # SYN
    print('Sending SYN')
    s.send('d\x00\x01\x00\x00\x00\x00\x00\x00\x00')

    # SYN_ACK(Recv)
    a = s.recv(4096)
    dump_data(a)
    u = list(a)
    print(u)
    u[0] = chr(ord(u[0]) + 1)
    u[-4] = chr(ord(u[-4]) + 1)
    a = "".join(u)
    print(u)

    # ACK(+1)
    print('Sending ACK + 1')
    s.send(a)
    print('\n---Accepted?---')
    dump_recv(s)
    print('---SHOULD BE "0 200"---\n')

    # USERNAME (Xeno)
    print('Sending username Xeno')
    s.send('\xc8\x00\x58\x65\x6e\x6f\x00\x00\x00\x00\x00\x00\x00\x00')
    print('\n---Room(s)?---')

    loop_dump_recv(s)

    # ROOM_JOIN /*201*/ (Room 01 as player)
    print('Joining room 1 as player')
    s.send('\xc9\x00\x01\x00\x00\x00\x00')
    dump_recv(s)
except IndexError, e:
    print("Invalid index\n" + e.message)
except KeyboardInterrupt, e:
    print(e)
except socket.timeout, e:
    print(e)
