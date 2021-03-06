#include "string.h"
#include "list.h"
#include <string>

String::String(const char* string) {
	if (!string) {
		length = 0;
		str = nullptr;
		return;
	}
	length = strlen(string);
	str = new char[length + 1];
	str[length] = '\0';
	memcpy(str, string, length);

	noDelete = false;
}

String::String(char* string, size_t length, bool noCopy) {
	if (!string) {
		this->length = 0;
		str = nullptr;
		return;
	}
	if (noCopy) {
		this->length = length;
		str = string;
		noDelete = true;
	} else {
		this->length = length;
		str = new char[length + 1];
		str[length] = '\0';
		memcpy(str, string, length);

		noDelete = false;
	}
}

String::String(const String& string) {
	this->length = string.length;

	str = new char[length + 1];
	str[length] = 0;
	memcpy(str, string.str, length);

	noDelete = false;
}

String::String(const String* string) {
	this->length = string->length;

	str = new char[length + 1];
	str[length] = 0;
	memcpy(str, string->str, length);

	noDelete = false;
}

String::String(String&& string) {
	this->length = 0;
	this->str = nullptr;
	*this = std::move(string);

	noDelete = false;
}

String::~String() {
	if (!noDelete) delete[] str;
	str = nullptr;
}

String& String::operator=(const String& string) {
	if (this != &string) {
		delete[] str;
		length = string.length;

		str = new char[length + 1];
		str[length] = 0;
		memcpy(str, string.str, length);
	}

	noDelete = false;

	return *this;
}

String& String::operator=(String&& string) {
	if (this != &string) {
		delete[] str;
		length = string.length;

		str = string.str;

		string.length = 0;
		string.str = nullptr;
	}

	noDelete = false;

	return *this;
}

String& String::Append(const char character) {
	char* tmpstr = str;
	str = new char[length + 2];
	str[length+1] = 0;
	memcpy(str, tmpstr, length);
	str[length] = character;

	length++;

	delete[] tmpstr;

	return *this;
}

String& String::Append(const String& string) {
	size_t newlen = length + string.length;
	char* tmpstr = str;
	str = new char[newlen + 1];
	str[newlen] = 0;
	memcpy(str, tmpstr, length);
	memcpy(str + length, string.str, string.length);
	length = newlen;

	delete[] tmpstr;

	return *this;
}

String& String::RemoveChars(const String& chars, bool iterate) {

	size_t start = 0;

	size_t failCount = 0;

	do {
		for (size_t c = 0; c < chars.length; c++) {
			start = Find(chars[c]);
			if (start != (size_t)-1) {
				Remove(start, start + 1);
				continue;
			}
			failCount++;
		}

		if (failCount >= chars.length) break;
		else failCount = 0;
	} while (iterate);

	return *this;
}

String& String::Remove(const String& string) {
	size_t index = Find(string);
	return Remove(index, index + string.length);
}

String& String::Remove(size_t start, size_t end) {
	size_t len = end - start;
	
	size_t newlen = length - len;

	char* tmp = str;

	str = new char[newlen + 1];
	memcpy(str, tmp, start);
	memcpy(str + start, tmp + start + len, newlen - start);

	length = newlen;
	str[length] = '\0';

	delete[] tmp;

	return *this;
}

String& String::RemoveBlankspace() {

	size_t start = Find(" ");
	while (start != ~0) {
		Remove(start, start + 1);
		start = Find(" ", start);
	}

	start = Find("\n");
	while (start != ~0) {
		Remove(start, start + 1);
		start = Find("\n", start);
	}

	start = Find("\r");
	while (start != ~0) {
		Remove(start, start + 1);
		start = Find("\r", start);
	}

	start = Find("\t");
	while (start != ~0) {
		Remove(start, start + 1);
		start = Find("\t", start);
	}

	return *this;
}

String String::SubString(size_t start, size_t end) const {
	return String(str + start, end - start);
}

size_t String::Count(const String& string, size_t offset) const {
	size_t total = length - string.length+1;
	if (total <= 0) return 0;
	size_t res = 0;
	for (size_t i = offset; i < total; i++) {
		bool match = true;
		for (size_t j = 0; j < string.length; j++) {
			if (str[i + j] != string[j]) {
				match = false;
				break;
			}
		}

		if (match)res++;
	}

	return res;
}

char String::operator[](size_t index) const {
	return str[index];
}

bool String::operator==(const String& string) const {
	if (length != string.length) return false;

	for (size_t i = 0; i < length; i++) {
		if (str[i] != string.str[i]) return false;
	}

	return true;
}

bool String::operator!=(const String& string) const {
	if (length != string.length) return true;

	for (size_t i = 0; i < length; i++) {
		if (str[i] == string.str[i]) return false;
	}

	return true;
}

String String::operator+(const String& string) const {
	return String(this).Append(string);
}

bool String::StartsWith(const String& string) const {
	if (length < string.length) return false;

	for (size_t i = 0; i < string.length; i++)
		if (str[i] != string.str[i]) return false;

	return true;
}

bool String::EndsWith(const String& string) const {
	if (length < string.length) return false;

	for (size_t i = 0; i < string.length; i++)
		if (str[length - i - 1] != string.str[string.length - i - 1]) return false;

	return true;
}

size_t String::Find(const String& string, size_t offset) const {
	if (length + offset < string.length) return (size_t)-1;
	for (size_t i = offset; i < length; i++) {
		bool match = true;
		for (size_t j = 0; j < string.length; j++) {

			if (str[i + j] != string.str[j]) {
				match = false;
				break;
			}
		}

		if (match) {
			return i;
		}
	}

	return (size_t)-1;
}

size_t String::Find(const char c, size_t offset) const {
	for (size_t i = offset; i < length; i++) {
		if (str[i] == c) return i;
	}

	return (size_t)-1;
}

List<String*> String::Split(const char delimiter) const {

	List<String*> list(128, 32);

	Split(delimiter, list);

	return list;
}

void String::Split(const char delimiter, List<String*>& list) const {
	size_t lastindex = 0;

	for (size_t i = 0; i < length; i++) {
		if (str[i] == delimiter) {

			list << new String(str + lastindex, i - lastindex);
			lastindex = i + 1;
		}
	}

	if (lastindex < length)
		list << new String(str + lastindex, length - lastindex);
}