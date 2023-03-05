#!/usr/bin/env python3
import sys
def l(fp) -> bytes:
    with open(fp, 'rb') as f:
        c = f.read()
    try:
        c.decode('utf-8')
        e = 'utf-8'
    except UnicodeDecodeError:
        try:
            c.decode('utf-16')
            e = 'utf-16'
        except UnicodeDecodeError:
            print("File is not UTF-8 or UTF-16 encoded")
            sys.exit(0)
    if e == 'utf-16':
        c = c.decode('utf-16').encode('utf-8')
    c = c.replace(b'\r\n', b'\n')
    return c

m = [ 108,57,4,83,15,175,248,19,64,176,206,31,17,24,17,44,5,22,127,7,90,82,24,84,12,76,73,62,73,92,84,90,92,93,28,10,73,24,31,26,16,166,223,19,8,27,70,4,27,173,200,49,169,158,127,17,82,94,176,213,67,54,3,82,66,4,65,18,2,0,12,29,20,0,0,20,14,24,113,75,165,254,17,26,15,18,170,194,83,19,17,6,30,27,76,67,28,44,20,2,25,51,27,72,73,58,179,238,89,43,5,91,91,78,154,136,83,20,66,80,81,190,203,172,202,83,184,205,78,29,166,226,84,24,65,154,201,15,9,8,59,27,21,94,64,92,69,190,219,4,75,0,30,74,0,26,81,83,19,0,94,4,183,254,1,29,58,84,71,19,25,17,15,21,246,254,29,18,123,244,152,67,20,21,73,31,183,224,82,19,15,81,177,215,74,181,204,84,99,85,58,92,44,28,23,84,29,183,158,127,10,25,94,24,164,220,13,8,71,83,24,27,21,11,1,176,210,14,79,82,53,3,22,20,8,175,254,14,30,85,19,84,3,87,30,155,250,2,13,127,0,172,168,127,25,4,20,54,10,85,86,100,85,60,102,91,71,85,80,25,8,170,198,83,19,18,71,26,10,127,1,173,141,127,12,9,15,71,37,86,240,148,81,73,67,190,199,172,202,93,91,57,21,178,175,29,2,82,66,21,84,53,12,182,254,0,247,233,82,90,13,25,64,58,88,18,69,88,74,70,19,3,73,10,83,20,6,0,0,246,235,31,16,6,19,171,198,60,2,92,59,94,82,96,1,27,71,156,209,26,95,8,164,220,70,26,14,83,26,82,31,13,28,2,156,198,21,177,200,169,220,70,26,2,93,91,59,23,24,17,26,240,222,154,192,76,7,45,183,201,64,49,24,20,89,37,8,81,3,1,42,22,69,91,241,152,94,8,72,73,61,22,1,26,81,179,196,127,30,1,19,59,9,76,19,18,52,78,21,84,20,67,93,20,21,29,168,222,190,203,77,86,241,205,6,82,69,31,84,53,12,83,52,24,240,211,4,84,17,2,90,60,86,28,21,121,92,69,185,253,172,242,176,214,17,11,178,168,82,10,95,2,164,247,12,44,15,246,254,80,26,92,18,2,92,42,94,82,99,2,27,21,10,170,194,23,21,23,170,195,79,7,58,75,0,82,19,5,25,165,196,174,210,91,2,16,30,31,175,142,83,49,162,205,28,54,7,70,57,85,52,8,3,54,10,244,250,11,127,70,89,78,91,75,20,93,53,6,27,24,26,87,71,19,69,47,6,7,81,48,19,22,162,202,113,61,63,99,20,77,88,16,70,26,14,83,15,3,65,12,85,7,166,235,84,3,17,127,19,22,50,176,168,82,2,94,6,76,93,48,91,83,88,86,25,82,93,16,0,15,176,214,183,196,90,19,24,27,91,86,15,15,73,44,30,247,196,30,182,171,83,25,240,242,3,6,95,2,18,9,15,73,29,9,21,27,4,161,206,84,47,25,0,1,14,0,20,8,8,69,83,53,21,85,28,29,15,19,29,58,165,225,9,52,183,201,246,254,87,0,89,42,16,243,218,5,156,151,243,149,20,67,21,30,14,27,168,210,22,2,20,6,23,38,176,229,29,85 ]
def f(m,k):
    return bytes([c^ord(k[i%len(k)]) for i,c in enumerate(m)]).decode('utf-8')

def c_h(ff, hv):
    import hashlib
    flags = l(ff).decode('utf-8').strip().split('\n')

    pps = 0
    for flag in flags:
        sed = flag.strip()
        f_h = hashlib.sha512(sed.encode('utf-8')).hexdigest()
        for h_pp in hv:
            h, p = h_pp.strip().split(':')
            if f_h == h.strip():
                print(f'Flag {flag} is correct.')
                pps += int(p)
                break
        else:
            print(f'Flag {flag} is WRONG!')

    print(f'Bodu: {pps}/10')
    if pps == 10:
        print(f(m,''.join(sorted(flags))))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python checker.py flags_file < .hashes_txt")
        sys.exit(0)
    ff = sys.argv[1]
    hv = sys.stdin.readlines()
    c_h(ff, hv)
