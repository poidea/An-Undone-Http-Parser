# -*- coding: utf-8 -*-

import __builtin__

def join_str(seq):
	return ''.join( list(seq) )

__builtin__.join_str = join_str
