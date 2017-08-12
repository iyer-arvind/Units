#!/usr/bin/python 

import math
import sys
import re

class Q(object):
    def __init__(self, factor, dims=[0, 0, 0, 0, 0, 0, 0], offset=0):
        if type(factor) is Q:
            q = factor
            self.factor = q.factor
            self.dims = q.dims[:]
            self.offset = q.offset

        else:
            self.factor = factor
            self.dims = dims
            self.offset = offset

    def __mul__(self, q):
        if isinstance(q, float) or isinstance(q, int):
            return Q(self.factor*q, self.dims, self.offset)

        if isinstance(q, Q):
            assert(self.offset == 0)
            assert(q.offset == 0)
            return Q(self.factor*q.factor, [i+j for i, j in zip(self.dims, q.dims)], 0)

        raise NotImplementedError

    __rmul__ = __mul__

    def __truediv__(self, q):
        assert(self.offset == 0)
        if isinstance(q, float) or isinstance(q, int):
            return Q(self.factor/q, self.dims, self.offset)

        if isinstance(q, Q):
            assert(q.offset == 0)
            return Q(self.factor/q.factor, [i-j for i, j in zip(self.dims, q.dims)], 0)

        raise NotImplementedError

    def __rtruediv__(self, q):
        assert(self.offset == 0)
        if isinstance(q, float) or isinstance(q, int):
            return Q(q/self.factor, [-i for i in self.dims], self.offset)

        if isinstance(q, Q):
            assert(q.offset == 0)
            return Q(q.factor/self.factor, [j-i for i, j in zip(self.dims, q.dims)], 0)

    def __pow__(self, q):
        assert(self.offset == 0)
        return Q(self.factor, [i*q for i in self.dims], 0)


    def __str__(self):
        return '{} {} ({})'.format(self.factor, str(self.dims), self.offset)


class UReg(dict):
    def __init__(self):
        self.update(
                {   'g': Q(0.001, [1, 0, 0, 0, 0, 0, 0], 0),
                    'm': Q(1.000, [0, 1, 0, 0, 0, 0, 0], 0),
                    's': Q(1.000, [0, 0, 1, 0, 0, 0, 0], 0),
                    'K': Q(1.000, [0, 0, 0, 1, 0, 0, 0], 0),
                    'A': Q(1.000, [0, 0, 0, 0, 1, 0, 0], 0),
                    'cd':Q(1.000, [0, 0, 0, 0, 0, 1, 0], 0),
                    'mol':   Q(1.000, [0, 0, 0, 0, 0, 0, 1], 0),
                    'rad': Q(1.000, [0, 0, 0, 0, 0, 0, 0], 0),
                    'pi':     Q(math.pi, [0, 0, 0, 0, 0, 0, 0], 0)
                })
        self._load_definitions()

    def _load_definitions(self):
        self.definitions = D = {}
        with open(sys.argv[1]) as fh:
            for l in fh:
                l = l[:l.find('#')]
                l = l.strip()
                if not l:
                    continue

                f = [i.strip() for i in l.split('=')]
                k = f[1]
                D[f[0]] = k 
                for v in f[2:]:
                    if(len(v)):
                        D[v] = k

    def __getitem__(self, key):
        if key in self:
            return self.get(key)

        if key in self.definitions:
            if ';' in self.definitions[key]:
                b, o = self.definitions[key].split(';')
                v = Q(eval(b, self))
                v.offset = float(o.replace('offset:', ''))
                self[key] = v
                return v

            else:
                v = Q(eval(self.definitions[key], self))
                self[key] = v
                return v

        for i in self.keys():
            if i.endswith('-'):
                if key.startswith(i[:-1]):
                    k = key[len(i)-1:]
                    self[key] = v = self[i]*self[k]
                    return v

        raise KeyError(key)

    def emit(self):
        n = 0
        for i in self.keys():
            n = max(len(i), n)
        
        self.pop('__builtins__')
        s = []
        for k in self:
            q = self[k]
            s.append('{{"{:s}", {{"{:s}", {:f}, {{{}}}, {} }}}}'.format(k, k, q.factor, ', '.join([str(i) for i in q.dims]), q.offset))
        print('{' + ',\n'.join(s) + '};')


if __name__ == '__main__':
    u = UReg()
    for k in u.definitions.keys():
        u[k]

    u.emit()
