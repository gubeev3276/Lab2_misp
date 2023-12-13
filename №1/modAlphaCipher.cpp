#include "modAlphaCipher.h"

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> codir = convert(open_text);
    for(unsigned i=0; i < codir.size(); i++) {
        codir[i] = (codir[i] + key[i % key.size()]) % alphaNum.size(); // Шифрование символа
    }
        codir[i] = (codir[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(codir);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s) // Преобразует строку в вектор с числами
{
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)// Преобразует обратно в строку 
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

std::wstring modAlphaCipher::getValidKey(const std::wstring & s)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty()) // Если строка пустая
        throw cipher_error("Empty key");
        
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw cipher_error(std::string("Key has invalid symbols: ")+st);
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}