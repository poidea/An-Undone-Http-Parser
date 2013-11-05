#  用python生成http parser（C）
python parser > http_parser.c

#  用astyle整理http parser的代码
astyle http_parser.c			\
		--style=ansi		\
		--indent=tab		\
		--suffix=none		\
		--quiet			\
		--lineend=linux		\
		--delete-empty-lines

#  为了工程的结构清晰，删除所有的已编译python文档
bash rm_bytes.sh

#  编译parser
gcc -g -c http_parser.c
gcc -g -o http_parser http_parser.o
