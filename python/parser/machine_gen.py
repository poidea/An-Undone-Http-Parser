# -*- coding: utf-8 -*-

import __builtin__
import util
import action_handler
import config

class StringHandler:

	"""对于状态机多字符转换的额外处理
	（因为对于字符串的条件无法按照原有的逻辑，
	  请注意条件之间是否有冲突，要避免产生“永远不会被访问的状态”）"""

	@staticmethod
	def launch(code, args):
		return eval("StringHandler.%s(args)" %  code.lower())

	@staticmethod
	def crlf(args):
		cond_word = 'else if'

		if args['logic_first']:
			cond_word = 'if'

		yield """
			%s ( ch == CR )
			{ }
			else if ( ch == LF )
			{
				%s
		""" % (cond_word, ActionHandler.launch(args))

		if args['next_stat'] != None:
			yield 'stat = stat_%s;' % args['next_stat']

		yield '}'

	@staticmethod
	def else_tag(args):
		yield 'else { %s' % join_str(ActionHandler.launch(args))

		if args['next_stat'] != None:
			yield 'stat = stat_%s;' % args['next_stat']

		yield '}'

	@staticmethod
	def no_cond(args):
		return join_str(ActionHandler.launch(args))


class MachineGenerator:
	"""返回状态机的解析器C程序"""

	@staticmethod
	def transfer_logic(node_name, conds):
		"""对自动机节点与节点之间状态转换过程的处理

		key	状态机节点的名称
		conds	该状态机节点的转换条件元组，若参与迭代，则有
			子元组cond = (条件, 目的地, 行为元组)"""

		cond_len = len(conds)

		for i, cond in enumerate(conds):
			for action_name in cond[2]:
				args = {
					'logic_first':		i == 0,
					'handler':		action_name,			#  调用行为元组
					'node_name':		node_name,
					'properties':		configuration.properties[node_name],
					'next_stat':		cond[1]
				}

				#  cond[0]是"条件"
				if cond[0][0] == '#':
					yield join_str(StringHandler.launch(cond[0][1:], args))

				else:
					cond_word = 'if'					#  i = 0
					if 0 < i < cond_len:
						cond_word = 'else if'

					elif i == cond_len:
						cond_word = 'else'

					yield """
						%s ( ch == %s )
						{
					""" % ( cond_word, cond[0] )

					yield join_str(ActionHandler.launch(args))

					if args['next_stat'] != None:
						yield 'stat = stat_%s;' % args['next_stat'];

					yield '}'


	@staticmethod
	def classify_stat():
		"""状态机所处状态的分类的生成，对每个状态在transfer_logic中进行逻辑细分"""

		for node_name, conds in configuration.links.iteritems():
			yield """
				case stat_%s:
					%s
					break;

			      """ % (node_name, \
				     join_str( \
					  MachineGenerator.transfer_logic(node_name, conds) \
				     ))

	@staticmethod
	def launch():
		return """
			void http_state_machine(char ch)
			{
				switch ( stat )
				{
				%s
				default:
					fprintf(stderr, "Parser error: no such state name.");
				}
			}

		""" % join_str(MachineGenerator.classify_stat())

	# -----------------------

	@staticmethod
	def gen_links():
		"""生成状态机的常量"""
		for i, key in enumerate(configuration.links.keys()):
			yield '#define stat_%s %s' % (key, str(i))

	@staticmethod
	def gen_c_buffers():
		"""生成C语言中的缓存变量"""
		for key, series in configuration.properties.iteritems():
			prop	= series[0]
			size    = series[1]

			if prop == 'unique':
				yield """
					char  buffer_%s[%d];

				""" % (key, size)

			elif prop == 'pair':
				parent = series[2]

				if parent != None:
					yield """
						char  buffer_%s[%d][%d];
						int   buffer_%s_len = 0;

					""" % ( key, 256, size, key )


__builtin__.MachineGenerator = MachineGenerator





