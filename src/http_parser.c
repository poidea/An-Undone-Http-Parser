/*
	*** SFI-Server ***
	function: Http Parser
*/

#include <string.h>
#include <stdio.h>
#include <malloc.h>

//  TOTAL
#define HEADER			0
#define PARAMETERS		1
#define QUERY_STRING	2
#define DATA			3
#define MULTI_DATA		4

//  Header
#define METHOD			5
#define PATH			6
#define PROTOCOL		7

//  Parameter
#define P_KEY			8
#define P_VAL			9

//  Querystring
#define Q_KEY			10
#define Q_VAL			11

//  Multidata
#define M_DATA			12

//  Charaters
#define CR				(char)13
#define LF				(char)10
#define SP				' '

//  Http Headers
#define GET				0
#define POST			1

//  Parsing parameters
#define P_CONTENT_TYPE	0
#define P_ACCEPT		1

//  These functions are to accelerate the comparation of string
//  Higher performance than strcmp in <string.h>

#define strcmp2(s, c0, c1) \
	s[0] == c0 && s[1] == c1

#define strcmp3(s, c0, c1, c2) \
	s[0] == c0 && s[1] == c1 && s[2] == c2

#define strcmp4(s, c0, c1, c2, c3) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3

#define strcmp5(s, c0, c1, c2, c3, c4) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 \
	&& s[4] == c4

#define strcmp6(s, c0, c1, c2, c3, c4, c5) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 \
	&& s[4] == c4 && s[5] == c5

#define strcmp7(s, c0, c1, c2, c3, c4, c5, c6) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 \
	&& s[4] == c4 && s[5] == c5 && s[6] == c6

#define strcmp8(s, c0, c1, c2, c3, c4, c5, c6, c7) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 \
	&& s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7

#define strcmp12(s, c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11) \
	s[0] == c0 && s[1] == c1 && s[2] == c2 && s[3] == c3 \
	&& s[4] == c4 && s[5] == c5 && s[6] == c6 && s[7] == c7 \
	&& s[8] == c8 && s[9] == c9 && s[10] == c10 && s[11] == c11

//  buffer functions

char buffer[4096];
int  buffer_len = 0;

void init_buffer(int size)
{
	buffer[0] = '\0';
	buffer_len = 0;
}

void add_buffer(char ch)
{
	buffer[buffer_len++] = ch;
}

void clear_buffer()
{
	buffer[0] = '\0';
	buffer_len = 0;
}

//  initialize the state machine

int  status    = HEADER;	//  Current parsing status.
//  You can refer to the constants that pre-defined
//  above.
int  sub_stat  = METHOD;

unsigned char  trim_flag = 1;
short int      crlf_count = 0;

//  here is the places to store the parsed value

struct header
{
	char method[10];
	char path[100];
	char protocol[10];

} header;

int para_len = 0;
struct parameters
{
	char key[20];
	char value[80];

} parameters[20];

//  these are quick link to the parameter values;
char* p_accept;
char* boundary = NULL;

int query_str_len = 0;
struct query_string
{
	char key[50];
	char value[50];

} query_string[20];

//  other vars

int  parsing_para = -1;		//  Current parsing parameter.
//  you can refer to the constant that pre-defined above.

char end_signal = 0;		//  determines if the request reaches the end.

//  here defines the functions

void http_header(char ch);
void http_parameters(char ch);
void http_query_string(char ch);
void http_multi_data(char ch);

void http_parse_parameter(int id, char ch);

/*
	Here is the entry of the http program.
*/
void http_request_parser(char ch)
{
	switch (status)
	{
	case HEADER:
		http_header(ch);
		break;

	case PARAMETERS:
		http_parameters(ch);
		break;

	case QUERY_STRING:
		http_query_string(ch);
		break;

	case MULTI_DATA:
		http_multi_data(ch);
		break;

	default:
		break;
	}
}

void http_header(char ch)
{
	switch (sub_stat)
	{
	case METHOD:
		if ( ch == SP )
		{
			sub_stat = PATH;
			add_buffer('\0');
			strcpy(header.method, buffer);
			clear_buffer();
		}
		else
		{
			add_buffer(ch);
		}
		break;

	case PATH:
		if ( ch == SP )
		{
			sub_stat = PROTOCOL;
			add_buffer('\0');
			strcpy(header.path, buffer);
			clear_buffer();
		}
		else
		{
			add_buffer(ch);
		}
		break;

	case PROTOCOL:
		if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			status = PARAMETERS;
			sub_stat = P_KEY;
			add_buffer('\0');
			strcpy(header.protocol, buffer);
			clear_buffer();
		}
		else
		{
			add_buffer(ch);
		}
		break;

	default:
		break;
	}
}

void http_parameters(char ch)
{
	switch (sub_stat)
	{
	case P_KEY:
		crlf_count = 0;
		if ( ch == SP )
			{ }
		else if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			status = QUERY_STRING;
			sub_stat = Q_KEY;
			clear_buffer();
		}
		else if ( ch == ':' )
		{
			sub_stat = P_VAL;
			add_buffer('\0');
			strcpy(parameters[para_len].key, buffer);
			clear_buffer();

			if ( strcmp12( parameters[para_len].key,
			               'C', 'o', 'n', 't', 'e', 'n', 't', '-', 'T', 'y', 'p', 'e') )
			{
				parsing_para = P_CONTENT_TYPE;
			}
			else if (strcmp6(parameters[para_len].key,
			                 'A', 'c', 'c', 'e', 'p', 't'))
			{
				parsing_para = P_ACCEPT;
			}
		}
		else
		{
			add_buffer(ch);
		}
		break;

	case P_VAL:
		//  trim_flag is to trim the extra spaces in the current tag.
		if ( trim_flag && ch == SP )
			{ }
		else if ( crlf_count == 0 )
		{
			if ( ch == CR )
				{ }
			else if ( ch == LF )
			{
				sub_stat = P_KEY;

				add_buffer('\0');
				strcpy(parameters[para_len].value, buffer);
				clear_buffer();

				para_len++;
				trim_flag = 1;
				crlf_count++;
			}
			else
			{
				http_parse_parameter(parsing_para, ch);
				trim_flag = 0;
			}
		}

		break;

	default:
		break;
	}
}

void http_parse_content_type( char ch );
void http_parse_parameter(int id, char ch)
{
	switch ( id )
	{
	case P_CONTENT_TYPE:
		http_parse_content_type(ch);
		break;

	case P_ACCEPT:
		add_buffer(ch);
		break;

	default:
		break;
	}
}

// CT for Content-Type

#define P_CT_KEY			0
#define P_CT_VALUE			1

#define P_CT_OTHER_STAT		0
#define P_CT_BOUNDARY		1

char ct_stat = P_CT_KEY;
char parsing_content_type = P_CT_OTHER_STAT;

void http_fill_content_type_args();

void http_parse_content_type( char ch )
{
	if ( ch == SP )
		{ }
	else if ( ch == ';' )
	{
		add_buffer('\0');
		http_fill_content_type_args();
		clear_buffer();
		ct_stat = P_CT_KEY;
	}
	else if ( ch == '=' )
	{
		if ( strcmp8( buffer, 'b', 'o', 'u', 'n', 'd', 'a', 'r', 'y' ) )
		{
			parsing_content_type = P_CT_BOUNDARY;
		}
		ct_stat = P_CT_VALUE;
	}
	else if ( ch == CR )
		{ }
	else if ( ch == LF )
	{
		add_buffer('\0');
		http_fill_content_type_args();
		ct_stat = P_CT_KEY;
	}
	else
	{
		add_buffer(ch);
	}
}

void http_fill_content_type_args()
{
	if ( parsing_content_type == P_CT_BOUNDARY )
	{
		boundary = (char*) malloc(strlen(buffer));
		strcpy( boundary, buffer );
		clear_buffer();
	}
	else
	{
		// --- do nothing ---
	}
}

void http_query_string(char ch)
{
	switch (sub_stat)
	{
	case Q_KEY:
		if ( ch == '=' )
		{
			sub_stat = Q_VAL;
			add_buffer('\0');
			strcpy(
			    query_string[query_str_len].key,
			    buffer
			);
			clear_buffer();
		}
		else
		{
			add_buffer(ch);
		}
		break;

	case Q_VAL:
		if ( ch == '&' )
		{
			sub_stat = Q_KEY;
			add_buffer('\0');
			strcpy(
			    query_string[query_str_len].value,
			    buffer
			);
			query_str_len++;
			clear_buffer();
		}
		else if ( ch == CR )
			{ }
		else if ( ch == LF )
		{
			status = MULTI_DATA;
			add_buffer('\0');
			strcpy(
			    query_string[query_str_len].value,
			    buffer
			);
			query_str_len++;
			clear_buffer();
		}
		else
		{
			add_buffer(ch);
		}
		break;

	default:
		break;
	}
}

void http_multi_data(char ch)
{

}

int main()
{
	char* msg = "GET http://localhost/photo/list HTTP/1.1\r\nAccept: Image/Gif\r\nContent-Type: text/html; boundary=----HTTP\r\n\r\n";

	for ( int i = 0; i < strlen(msg); i++)
	{
		http_request_parser(msg[i]);
	}

	printf("%s %s %s\n",    header.method, header.path, header.protocol);
	printf("%s: %s\n",		parameters[0].key, parameters[0].value);
	printf("%s: %s\n\n",    parameters[1].key, parameters[1].value);

	printf("%s",			boundary);

	// printf("%s: %s\n",	query_string[0].key, query_string[0].value);
	// printf("%s: %s\n",	query_string[1].key, query_string[1].value);

	return 0;
}



