# -*- coding: utf-8 -*-

import accelerator
import action_handler
import config
import debug
import machine_gen
import static
import util

if __name__ == '__main__':

	print incs
	for val in gen_const():
		print val

	for val in MachineGenerator.gen_links():
		print val

	for val in gen_strcmp(20):
		print val

	print static_code
	for val in MachineGenerator.gen_c_buffers():
		print val

	print MachineGenerator.launch()
	print c_main()





