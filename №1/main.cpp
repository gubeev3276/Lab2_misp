#include <locale>
#include <iostream>
#include "modAlphaCipher.h"
#include <sstream>
using namespace std;
std::wstring toValidtext(wstring& s) // Проверяет строку на то, чтобы она состояла только из прописных букв
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Нет текста!!");
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw cipher_error(std::string("Недопустимые символы: ")+st);
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

int main(int argc, char **argv)
{
    try {
        locale loc("ru_RU.UTF-8");
        locale::global(loc);
        wstring key;
        wstring text;
        unsigned op;
        wcout<<"Введите ключ: ";
        wcin>>key;
        wcout<<"Ключ загружен. Обработка...\n";
        modAlphaCipher cipher(key);
        do {
            wcout<<"Выберите операцию (0-выйти, 1-зашифровать, 2-расшифровать): ";
            wcin>>op;
            if (op > 2) {
                throw(cipher_error("Недоступная операция!"));
            } else if (op >0) {
                wcout<<"Введите текст: ";
                wcin>>text;
                std::wstring vtext=toValidtext(text);
                if (op==1) {
                    wcout<<"Зашифрованный текст: "<<cipher.encrypt(vtext)<<endl;
                } else {
                    wcout<<"Расшифрованный текст: "<<cipher.decrypt(vtext)<<endl;
                }
            }
        } while (op!=0);

    } catch(const cipher_error& e) {
        std::wcerr<<e.what()<<std::endl;
    }
    return 0;
}