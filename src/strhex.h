
#include <string>

__inline static char s2c(short s)
{
	const char * a = "\x10\x01\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30___7___\x41\x41\x41\x41\x41\x41____________26____________\x61\x61\x61\x61\x61\x61\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00___7___\x0A\x0A\x0A\x0A\x0A\x0A____________26____________\x0a\x0a\x0a\x0a\x0a\x0a";
	char c = 0;
	for (int i = 0; i < sizeof(s); i++)
	{
		c += a[i] * (((char *)&s)[i] - a[((char *)&s)[i] - '0' + sizeof(short)] + a[((char *)&s)[i] - '0' + ('f' - '0') + sizeof(char) + sizeof(short)]);
	}
	return c;
}
__inline static short c2s(char c)
{
	const char * a = "\xF0\x0F\x04\x00\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x41\x42\x43\x44\x45\x46";
	short s = 0;
	for (int i = 0; i < sizeof(s); i++)
	{
		((char*)&s)[i] = a[((unsigned char)(c & a[i]) >> a[i + sizeof(short)]) + sizeof(short) + sizeof(short)];
	}

	return s;
}
__inline static std::string hex2str(std::string s)
{
	std::string h(s.size() * sizeof(short), '\0');
	for (size_t i = 0; i < s.size(); i++)
	{
		((short*)h.c_str())[i] = c2s(s.at(i));
	}
	return h;
}
__inline static std::string str2hex(std::string h)
{
	std::string s(h.length() / sizeof(short), '\0');
	for (size_t i = 0; i < s.length(); i++)
	{
		s.at(i) = s2c(((short*)h.c_str())[i]);
	}
	return s;
}
__inline static std::string str_xor(std::string s)
{
	std::string x(s);
	for (auto c : x){ c ^= (unsigned char)(0xFF); }
	return x;
}
__inline static std::string hex_to_str(std::string h)
{
	std::string s((""));
	for (auto c : h) {char ch[sizeof(short) + 1] = { 0 }; sprintf_s(ch, ("%02X"), (unsigned char)c);s.append(ch); }
	return s;
}
__inline static std::string str_to_hex(std::string s)
{
	std::string h((""));
	for (size_t i = 0; i < s.length(); i += sizeof(short))
	{
		h.push_back((unsigned char)(int)std::strtoul(s.substr(i, sizeof(short)).c_str(), NULL, 0x10));
	}
	return h;
}
#include <sstream>

std::string str_to_hex_2(const std::string& str)
{
	std::stringstream ss;
	const std::string hex = ("0123456789ABCDEF");
	for (std::size_t i = 0; i < str.size(); i++)
	{
		ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xF];
	}
	return ss.str();
}

std::string hex_to_str_2(const std::string& hex)
{
	std::string result = ("");
	for (std::size_t i = 0; i < hex.length(); i += sizeof(short))
	{
		result.push_back((unsigned char)(int)std::strtol(hex.substr(i, sizeof(short)).c_str(), NULL, 0x10));
	}
	return result;
}

__inline static void hex_str(unsigned char *inchar, unsigned int len, unsigned char *outtxt)
{
	unsigned int i = 0x00;
	unsigned char hbit = 0x00, lbit = 0x00;
	for (i = 0x00;i < len;i++)
	{
		hbit = (*(inchar + i) & 0xF0) >> 0x04;
		lbit = *(inchar + i) & 0x0F;
		if (hbit > 0x09)
		{
			outtxt[0x02 * i] = 'A' + hbit - 0x0A;
		}
		else
		{
			outtxt[0x02 * i] = '0' + hbit;
		}
		if (lbit > 0x09)
		{
			outtxt[0x02 * i + 1] = 'A' + lbit - 0x0A;
		}
		else
		{
			outtxt[0x02 * i + 1] = '0' + lbit;
		}
	}
	outtxt[0x02 * i] = 0x00;
}
__inline static unsigned int str_hex(unsigned char *str, unsigned char *hex)
{
	unsigned int num = 0x00;
	unsigned char ctmp = 0x00, ctmp1 = 0x00, half = 0x00;
	do
	{
		do
		{
			half = 0x00;
			ctmp = *str;
			if (!ctmp)
			{
				break;
			}
			str++;
		} while ((ctmp == 0x20) || (ctmp == 0x2c) || (ctmp == '\t'));
		if (!ctmp)
		{
			break;
		}
		if (ctmp >= 'a')
		{
			ctmp = ctmp - 'a' + 0x0A;
		}
		else if (ctmp >= 'A')
		{
			ctmp = ctmp - 'A' + 0x0A;
		}
		else
		{
			ctmp = ctmp - '0';
		}
		ctmp = ctmp << 0x04;
		half = 0x01;
		ctmp1 = *str;
		if (!ctmp1)
		{
			break;
		}
		str++;
		if ((ctmp1 == 0x20) || (ctmp1 == 0x2c) || (ctmp1 == '\t'))
		{
			ctmp = ctmp >> 0x04;
			ctmp1 = 0x00;
		}
		else if (ctmp1 >= 'a')
		{
			ctmp1 = ctmp1 - 'a' + 0x0A;
		}
		else if (ctmp1 >= 'A')
		{
			ctmp1 = ctmp1 - 'A' + 0x0A;
		}
		else
		{
			ctmp1 = ctmp1 - '0';
		}
		ctmp += ctmp1;
		*hex = ctmp;
		hex++;
		num++;
	} while (1);
	if (half)
	{
		ctmp = ctmp >> 0x04;
		*hex = ctmp;
		num++;
	}
	return(num);
}