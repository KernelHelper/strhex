
#include <string>

__inline static char s2c(short s)
{
	char * a = "\x10\x01\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30___7___\x41\x41\x41\x41\x41\x41____________26____________\x61\x61\x61\x61\x61\x61\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00___7___\x0A\x0A\x0A\x0A\x0A\x0A____________26____________\x0a\x0a\x0a\x0a\x0a\x0a";
	char c = 0;
	for (int i = 0; i < sizeof(s); i++)
	{
		c += a[i] * (((char *)&s)[i] - a[((char *)&s)[i] - '0' + sizeof(short)] + a[((char *)&s)[i] - '0' + ('f' - '0') + sizeof(char) + sizeof(short)]);
	}
	return c;
}
__inline static short c2s(char c)
{
	char * a = "\xF0\x0F\x04\x00\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x41\x42\x43\x44\x45\x46";
	short s = 0;
	for (int i = 0; i < sizeof(s); i++)
	{
		((char*)&s)[i] = a[((unsigned char)(c & a[i]) >> a[i + sizeof(short)]) + sizeof(short) + sizeof(short)];
	}

	return s;
}
__inline static std::string str2hex(std::string s)
{
	std::string h(s.length() * sizeof(short), '\0');
	for (int i = 0; i < s.length(); i++)
	{
		((short*)h.c_str())[i] = c2s(s.at(i));
	}
	return h;
}
__inline static std::string hex2str(std::string h)
{
	std::string s(h.length() / sizeof(short), '\0');
	for (int i = 0; i < s.length(); i++)
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
	char ch[3] = { 0 };
	for (auto c : h) { sprintf(ch, ("%02X"), (unsigned char)c);s.append(ch); }
	return s;
}
__inline static std::string str_to_hex(std::string s)
{
	std::string h((""));
	size_t i = 0;
	size_t l = s.length();
	if (!(l % sizeof(short)))
	{
		for (i = 0; i < l; i += sizeof(short))
		{
			h.push_back((unsigned char)strtoul(s.substr(i, sizeof(short)).c_str(), NULL, 0x10));
		}
	}
	return h;
}