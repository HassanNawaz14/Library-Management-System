#pragma once
#include <windows.h>
#include <iostream>
#include <string>

class ColorUtils {
private:
    static void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

public:
    struct Colors {
        static const int SUCCESS = 10;      // Bright Green
        static const int ERROR1 = 12;        // Bright Red
        static const int WARNING = 14;      // Bright Yellow
        static const int INFO = 11;         // Bright Cyan
        static const int TITLE = 13;        // Bright Magenta
        static const int HEADER = 9;        // Bright Blue
        static const int NORMAL = 7;        // Default White
        static const int HIGHLIGHT = 14;    // Bright Yellow
    };

    static void printSuccess(const std::string& message) {
        setColor(Colors::SUCCESS);
        std::cout << "✓ " << message << std::endl;
        setColor(Colors::NORMAL);
    }

    static void printError(const std::string& message) {
        setColor(Colors::ERROR1);
        std::cout << "✗ " << message << std::endl;
        setColor(Colors::NORMAL);
    }

    static void printWarning(const std::string& message) {
        setColor(Colors::WARNING);
        std::cout << "! " << message << std::endl;
        setColor(Colors::NORMAL);
    }

    static void printInfo(const std::string& message) {
        setColor(Colors::INFO);
        std::cout << "ℹ " << message << std::endl;
        setColor(Colors::NORMAL);
    }

    static void printHeader(const std::string& title) {
        setColor(Colors::HEADER);
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "   " << title << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        setColor(Colors::NORMAL);
    }

    static void printTitle(const std::string& title) {
        setColor(Colors::TITLE);
        std::cout << "\n" << std::string(40, '-') << std::endl;
        std::cout << "  " << title << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        setColor(Colors::NORMAL);
    }

    static void highlightText(const std::string& text) {
        setColor(Colors::HIGHLIGHT);
        std::cout << text;
        setColor(Colors::NORMAL);
    }
};