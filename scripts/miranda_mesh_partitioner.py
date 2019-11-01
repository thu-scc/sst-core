import re


elements = dict()


with open('partition2.log', 'r') as fi:
    for line in fi:
        if line.find('(ID=') > -1:
            lc = line.strip().split(' ')
            ename = lc[0]
            cid = int(lc[1].split('=')[-1].split(')')[0])
            # rk = re.split(r'_|\.', name)[-1]
            vls = re.split(r'\.|_', ename)
            name, rk, = vls[0], int(vls[-1])
            if re.match(r'l.cache', name) is not None or name == 'cpu':
                if rk > 15:
                    rk += 2
                elif rk > 11:
                    rk += 1
            elif name == 'mem':
                if rk == 0:
                    rk = 12
                else:
                    rk = 17
            if rk % 6 < 3:
                if rk // 6 == 2 or ((rk // 6 == 1 or rk // 6 == 2) and rk % 6 < 2):
                    th = 0
                else:
                    th = 1
                rk = 0
            else:
                if rk // 6 == 2 or ((rk // 6 == 1 or rk // 6 == 2) and rk % 6 > 3):
                    th = 0
                else:
                    th = 1
                rk = 1
            th = 0
            print('{} {}'.format(cid, (rk << 16) + th))
