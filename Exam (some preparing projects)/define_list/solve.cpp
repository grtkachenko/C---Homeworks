#include <iostream>
#define CAT(a, b) CAT2(a, b)
#define CAT2(a, b) a##b


#define SEQ_0(fake) SEQ_1
#define SEQ_1(fake) SEQ_2
#define SEQ_2(fake) SEQ_3
#define SEQ_3(fake) SEQ_4
#define SEQ_6(fake) std::cout << "OVERFLOW";

#define FINISH_SEQ_0(seq) ERROR
#define FINISH_SEQ_1(seq) TAKE_0 seq
#define FINISH_SEQ_2(seq) TAKE_1 seq
#define FINISH_SEQ_3(seq) TAKE_2 seq

#define TAKE_0(arg) arg
#define TAKE_1(_) TAKE_0
#define TAKE_2(_) TAKE_1

#define BACK(seq) CAT(FINISH_, SEQ_0 seq)(seq)


int main () {
    std::cout << BACK((5)(6)(7)) << " " << TAKE_0(7);
	system("pause");
}

