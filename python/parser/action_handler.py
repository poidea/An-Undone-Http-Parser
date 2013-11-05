# -*- coding: utf-8 -*-

import __builtin__
import util

#  解析行为映射整理

class ActionHandler:
	"""对自动机行为的处理"""

	@classmethod
	def launch(cls, args):
		"""关于args的定义：
		logic_first	->	是否为第一个if
		handler		->	调用的行为名称
		node_name	->	所处在的状态节点名
		property	->	属性
		next_stat	->	下一个节点的名称"""

		return join_str(getattr(cls(), args['handler'])(args))

	@staticmethod
	def record(args):
		property_name = args['properties'][0]

		yield 'add_buffer(0);'

		if property_name == 'unique':
			yield 'strcpy(buffer_%s, buffer);' % (args['node_name'])

		elif property_name == 'pair':
			node_name = args['properties'][2]
			if node_name != None:
				node_name = args['node_name']

			yield 'strcpy(buffer_%s[buffer_%s_len++], buffer);' % (node_name, node_name)
			
		yield 'clear_buffer();'

	@staticmethod
	def save_char(args):
		yield 'add_buffer(ch);'

	@staticmethod
	def do_nothing(args):
		return ''


__builtin__.ActionHandler = ActionHandler




