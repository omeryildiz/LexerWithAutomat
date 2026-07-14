#ifndef LEXER_H
#define LEXER_H

#include <QChar>
#include <QString>
#include <QVector>

class Lexer
{
public:
    enum class TokenType {
        ParenthesisOrBrace,
        PlusOrMinus,
        IntegerLiteral,
        FloatLiteral,
        KeywordWhile,
        KeywordIf,
        KeywordInt,
        Assignment,
        Separator,
        RelationalOperator,
        CompoundAssignment,
        ComparisonOperator,
        Identifier
    };

    struct Token {
        TokenType type;
        QString lexeme;
        int line;
        int column;
    };

    struct Error {
        QChar character;
        int line;
        int column;
        QString message;
    };

    struct Result {
        QVector<Token> tokens;
        QVector<Error> errors;
    };

    Result tokenize(const QString &source) const;

    static QString tokenTypeToString(TokenType type);
};

#endif // LEXER_H
