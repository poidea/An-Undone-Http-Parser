
#include <stdio.h>
#include <string.h>

#define LF (char)10
#define CR (char)13
#define SP ' '
#define stat_q_key 0
#define stat_protocol 1
#define stat_break_2 2
#define stat_break_1 3
#define stat_p_key 4
#define stat_path 5
#define stat_q_val 6
#define stat_p_val 7
#define stat_method 8
#define strcmp1(s, c0) s[0] == c0
#define strcmp2(s, c0, c1) s[0] == c0 && s[1] == c1
#define strcmp3(s, c0, c1, c2) s[0] == c0 && s[1] == c1 && s[2] == c2
#define strcmp4(s, c0, c1, c2, c3) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3
#define strcmp5(s, c0, c1, c2, c3, c4) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4
#define strcmp6(s, c0, c1, c2, c3, c4, c5) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5
#define strcmp7(s, c0, c1, c2, c3, c4, c5, c6) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6
#define strcmp8(s, c0, c1, c2, c3, c4, c5, c6, c7) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7
#define strcmp9(s, c0, c1, c2, c3, c4, c5, c6, c7, c8) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8
#define strcmp10(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9
#define strcmp11(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10
#define strcmp12(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11
#define strcmp13(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12
#define strcmp14(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13
#define strcmp15(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14
#define strcmp16(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14 && s[15] == c15
#define strcmp17(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14 && s[15] == c15 && s[16] == c16
#define strcmp18(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14 && s[15] == c15 && s[16] == c16 && s[17] == c17
#define strcmp19(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14 && s[15] == c15 && s[16] == c16 && s[17] == c17 && s[18] == c18
#define strcmp20(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19) s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 && s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 && s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11 && s[12] == c12 && s[13] == c13 && s[14] == c14 && s[15] == c15 && s[16] == c16 && s[17] == c17 && s[18] == c18 && s[19] == c19


char buffer[4096];
int  buffer_len = 0;

int  stat     = stat_method;

void init_buffer(int size)
{
	buffer[0] = 0;
	buffer_len = 0;
}

void add_buffer(char ch)
{
	buffer[buffer_len++] = ch;
}

void clear_buffer()
{
	buffer[0] = 0;
	buffer_len = 0;
}


char  buffer_protocol[15];



char  buffer_p_key[256][256];
int   buffer_p_key_len = 0;



char  buffer_q_val[256][256];
int   buffer_q_val_len = 0;



char  buffer_q_key[256][256];
int   buffer_q_key_len = 0;



char  buffer_break_2[256][256];
int   buffer_break_2_len = 0;



char  buffer_break_1[256][256];
int   buffer_break_1_len = 0;



char  buffer_path[256];



char  buffer_p_val[256][256];
int   buffer_p_val_len = 0;



char  buffer_method[10];



void http_state_machine(char ch)
{
	switch ( stat )
	{
	case stat_q_key:
		if ( ch == '=' )
		{
			add_buffer(0);
			strcpy(buffer_q_key[buffer_q_key_len++], buffer);
			clear_buffer();
			stat = stat_q_val;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_protocol:
		if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			add_buffer(0);
			strcpy(buffer_protocol, buffer);
			clear_buffer();
			stat = stat_p_key;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_break_2:
		if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
		}
		break;
	case stat_break_1:
		if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			stat = stat_q_key;
		}
		else
		{
			add_buffer(ch);
			stat = stat_p_key;
		}
		break;
	case stat_p_key:
		if ( ch == ':' )
		{
			add_buffer(0);
			strcpy(buffer_p_key[buffer_p_key_len++], buffer);
			clear_buffer();
			stat = stat_p_val;
		}
		else if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			add_buffer(0);
			strcpy(buffer_p_key[buffer_p_key_len++], buffer);
			clear_buffer();
			stat = stat_break_2;
		}
		else if ( ch == '&' )
		{
			add_buffer(0);
			strcpy(buffer_p_key[buffer_p_key_len++], buffer);
			clear_buffer();
			stat = stat_q_key;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_path:
		if ( ch == SP )
		{
			add_buffer(0);
			strcpy(buffer_path, buffer);
			clear_buffer();
			stat = stat_protocol;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_q_val:
		if ( ch == '&' )
		{
			add_buffer(0);
			strcpy(buffer_q_val[buffer_q_val_len++], buffer);
			clear_buffer();
			stat = stat_q_key;
		}
		else if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			add_buffer(0);
			strcpy(buffer_q_val[buffer_q_val_len++], buffer);
			clear_buffer();
			stat = stat_break_2;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_p_val:
		if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			add_buffer(0);
			strcpy(buffer_p_val[buffer_p_val_len++], buffer);
			clear_buffer();
			stat = stat_break_1;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	case stat_method:
		if ( ch == SP )
		{
			add_buffer(0);
			strcpy(buffer_method, buffer);
			clear_buffer();
			stat = stat_path;
		}
		else
		{
			add_buffer(ch);
		}
		break;
	default:
		fprintf(stderr, "Parser error: no such state name.");
	}
}



int main()
{
	char* text = "POST http://localhost/ HTTP/1.1\r\nHost: localhost\r\nAccept: text/html\r\n\r\ntest=1&test2=2\r\n\r\n\0";
	while ( (int)*text != 0 )
	{
		http_state_machine( *text );
		text++;
	}
	printf("TEST VALUE: %s\n", buffer_q_val[0]);
	return 0;
}


