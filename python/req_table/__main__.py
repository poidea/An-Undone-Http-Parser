class SFI_Hash:
	"""生成C语言中HTTP协议常用属性的哈希表"""

	def __init__(self, table_size):
		#  表格大小
		self.table_size = table_size

	def get_id(self, key):
		total = reduce(
				lambda x, y: x + y,		
				[int(ord(ch)) for ch in key], 0
			)
		return total % self.table_size

	@staticmethod
	def c_hash():
		return """

			int hash(char* key, int table_size)
			{
				unsigned int hash_val = 0;
				while ( (unsigned int)*key != 0 )
					hash_val += (unsigned int) key++;
	
				return hash_val % table_size;
			}
		"""


if __name__ == '__main__':

	sfi_hash = SFI_Hash(5)

	print SFI_Hash.c_hash()
