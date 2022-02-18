#ifndef INT_SIGNAL_TYPES_HPP
#define INT_SIGNAL_TYPES_HPP

enum class Int_signal
{
    ADD,
    ASSIGN_ADD,
    PREF_INC,
    POST_INC,
    SUB,
    ASSIGN_SUB,
    PREF_DEC,
    POST_DEC,
    MUL,
    ASSIGN_MUL,
    DIV,
    ASSIGN_DIV,
    ASSIGN_COPY,
    ASSIGN_MOVE,
    COPY,
    MORE,
    MORE_EQ,
    LESS,
    LESS_EQ,
    EQ,
    NOT_EQ,
    MOVE,
    CONSTRUCT,
    DESTRUCT
};

#endif // INT_SIGNAL_TYPES_HPP
