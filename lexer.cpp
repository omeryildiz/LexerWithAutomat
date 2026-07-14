#include "lexer.h"

namespace {

bool isIdentifierStart(const QChar character)
{
    return character.isLetter() || character == QChar('_');
}

bool isIdentifierPart(const QChar character)
{
    return character.isLetterOrNumber() || character == QChar('_');
}

void advancePosition(const QChar character, int &line, int &column)
{
    if (character == QChar('\n')) {
        ++line;
        column = 1;
        return;
    }

    ++column;
}

Lexer::TokenType keywordOrIdentifier(const QString &lexeme)
{
    if (lexeme == QStringLiteral("while")) {
        return Lexer::TokenType::KeywordWhile;
    }

    if (lexeme == QStringLiteral("if")) {
        return Lexer::TokenType::KeywordIf;
    }

    if (lexeme == QStringLiteral("int")) {
        return Lexer::TokenType::KeywordInt;
    }

    return Lexer::TokenType::Identifier;
}

} // namespace

Lexer::Result Lexer::tokenize(const QString &source) const
{
    Result result;
    int index = 0;
    int line = 1;
    int column = 1;

    while (index < source.size()) {
        const QChar character = source.at(index);

        if (character.isSpace()) {
            advancePosition(character, line, column);
            ++index;
            continue;
        }

        const int tokenLine = line;
        const int tokenColumn = column;

        const auto appendToken = [&](const TokenType type, const int length) {
            result.tokens.append({type, source.mid(index, length), tokenLine, tokenColumn});
            for (int offset = 0; offset < length; ++offset) {
                advancePosition(source.at(index + offset), line, column);
            }
            index += length;
        };

        switch (character.unicode()) {
        case '(':
        case ')':
        case '{':
        case '}':
            appendToken(TokenType::ParenthesisOrBrace, 1);
            continue;
        case '+':
        case '-':
            if (index + 1 < source.size() && source.at(index + 1) == QChar('=')) {
                appendToken(TokenType::CompoundAssignment, 2);
            } else {
                appendToken(TokenType::PlusOrMinus, 1);
            }
            continue;
        case '=':
            if (index + 1 < source.size() && source.at(index + 1) == QChar('=')) {
                appendToken(TokenType::ComparisonOperator, 2);
            } else {
                appendToken(TokenType::Assignment, 1);
            }
            continue;
        case ';':
        case ',':
            appendToken(TokenType::Separator, 1);
            continue;
        case '<':
        case '>':
            appendToken(TokenType::RelationalOperator, 1);
            continue;
        default:
            break;
        }

        if (character.isDigit()) {
            const int start = index;
            while (index < source.size() && source.at(index).isDigit()) {
                advancePosition(source.at(index), line, column);
                ++index;
            }

            TokenType type = TokenType::IntegerLiteral;
            if (index + 1 < source.size()
                && source.at(index) == QChar('.')
                && source.at(index + 1).isDigit()) {
                type = TokenType::FloatLiteral;
                advancePosition(source.at(index), line, column);
                ++index;

                while (index < source.size() && source.at(index).isDigit()) {
                    advancePosition(source.at(index), line, column);
                    ++index;
                }
            }

            result.tokens.append({type, source.mid(start, index - start), tokenLine, tokenColumn});
            continue;
        }

        if (isIdentifierStart(character)) {
            const int start = index;
            while (index < source.size() && isIdentifierPart(source.at(index))) {
                advancePosition(source.at(index), line, column);
                ++index;
            }

            const QString lexeme = source.mid(start, index - start);
            result.tokens.append({keywordOrIdentifier(lexeme), lexeme, tokenLine, tokenColumn});
            continue;
        }

        result.errors.append({
            character,
            tokenLine,
            tokenColumn,
            QStringLiteral("Unexpected character '%1'.").arg(character)
        });
        advancePosition(character, line, column);
        ++index;
    }

    return result;
}

QString Lexer::tokenTypeToString(const TokenType type)
{
    switch (type) {
    case TokenType::ParenthesisOrBrace:
        return QStringLiteral("TOKEN_BRACE_PAREN");
    case TokenType::PlusOrMinus:
        return QStringLiteral("TOKEN_PLUS_MINUS");
    case TokenType::IntegerLiteral:
        return QStringLiteral("TOKEN_INTEGER_LITERAL");
    case TokenType::FloatLiteral:
        return QStringLiteral("TOKEN_FLOAT_LITERAL");
    case TokenType::KeywordWhile:
        return QStringLiteral("TOKEN_WHILE");
    case TokenType::KeywordIf:
        return QStringLiteral("TOKEN_IF");
    case TokenType::KeywordInt:
        return QStringLiteral("TOKEN_INT");
    case TokenType::Assignment:
        return QStringLiteral("TOKEN_ASSIGN");
    case TokenType::Separator:
        return QStringLiteral("TOKEN_SEPARATOR");
    case TokenType::RelationalOperator:
        return QStringLiteral("TOKEN_RELATIONAL");
    case TokenType::CompoundAssignment:
        return QStringLiteral("TOKEN_ASSIGN_PLUS_MINUS");
    case TokenType::ComparisonOperator:
        return QStringLiteral("TOKEN_COMPARE");
    case TokenType::Identifier:
        return QStringLiteral("TOKEN_IDENTIFIER");
    }

    return QStringLiteral("TOKEN_UNKNOWN");
}
