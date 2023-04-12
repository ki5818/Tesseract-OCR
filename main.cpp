#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include <windows.h>
#include <iostream>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

char* UTF8ToANSI(const char* pszCode);

int main()
{
    const char* input_image = "D:/Program Files/Visual Studio 2022/Tesseract-OCR/image/img.png";

    // tesseract api 설정
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("D:/Program Files/Tesseract-OCR/tessdata", "kor")) {
        return -1;
    }

    // 이미지 설정
    Pix* image = pixRead(input_image);
    api->SetImage(image);

    std::string utf_text = api->GetUTF8Text();
    std::string text = UTF8ToANSI(utf_text.c_str());

    std::cout << text << std::endl;
}

char* UTF8ToANSI(const char* pszCode)
{
    BSTR    bstrWide;
    char* pszAnsi;
    int     nLength;

    // Get nLength of the Wide Char buffer
    nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1,
        NULL, NULL);
    bstrWide = SysAllocStringLen(NULL, nLength);

    // Change UTF-8 to Unicode (UTF-16)
    MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

    // Get nLength of the multi byte buffer
    nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
    pszAnsi = new char[nLength];

    // Change from unicode to mult byte
    WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
    SysFreeString(bstrWide);

    return pszAnsi;
}