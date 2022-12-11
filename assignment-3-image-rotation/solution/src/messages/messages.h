//
// Created by oleg on 25.11.22.
//

#ifndef IMAGE_TRANSFORMER_MESSAGES_H
#define IMAGE_TRANSFORMER_MESSAGES_H
enum sys_words {
    WELCOME,
    FATAL_ERROR,
    FINISHED,
    NOT_THE_RIGHT_NUMBER_OF_ARGS,
    PROBLEM_IN_READING,
};
extern const char *const messages[];//Сообщения для юзера
#endif //IMAGE_TRANSFORMER_MESSAGES_H
