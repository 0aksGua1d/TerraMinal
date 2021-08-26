#pragma once

#include <string>
#include <codecvt>
#include <locale>

static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> string_converter;
