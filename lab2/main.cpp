#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

string const RULES = "2.5. Игра «21 палочка». \nИграют двое (один из них компьютер). У"
"каждого 100 баллов. \nНа столе находятся 21 палочка (вместо палочек могут"
"быть любые предметы). \nХоды делаются игроками по очереди. За один ход"
"игрок берёт себе со стола одну, две или три палочки. \nИгрок, который возьмёт"
"последнюю палочку со стола, проигрывает. \nС проигравшего списывается 15"
"балов, а победителю прибавляется 15 Пропускать ход нельзя. \nИгра"
"заканчивается пока у игроков есть баллы.\n\n";

void print_with_sleep(string s) {

    for (char sym: s) {
        cout << sym << flush;
        usleep(55000);
    }
}
void turn(int &stics, int cnt, string name) {
    stics -= cnt;
    cout << name << " забирает " << cnt << " палочек из кучи!" << '\n';
}



string game_with_bot(

    int all_turn_option[],
    int size_turns,
    int all_sticks,
    int first_turn = 0) {
    string player = "Player";
    string bot = "Bot";
    string winner;
    int turns_cnt = 1;
    if (first_turn % 2 == 0) {
        print_with_sleep(format("Первый ход делает {}\n", player));
    } else {
        print_with_sleep(format("Первый ход делает {}\n", bot));
    }
    while (all_sticks > 0) {
        print_with_sleep( "Ход " + to_string(turns_cnt) + ". ");
        print_with_sleep( "Палочек в куче - " +  to_string(all_sticks) + "\n");
        int num = -1;
        if (first_turn % 2 == 0) {
            while (num == -1) {
                try {
                    cin >> num;
                }
                catch (...) {
                    cout << "Что бы сделать ход - введите допустимую цифру";
                    num = -1;
                }
                if (count(& all_turn_option[0] ,& all_turn_option[size_turns] ,num) > 0) {
                    turn(all_sticks,num,player);
                    winner = bot;
                }
                else {
                    // do logic like all_stics < turns_cnt and players need to do another turn
                    num = -1;
                    string all_vars_str = "";
                    for (int i = 0; i < size_turns; i++) {
                        if (i == size_turns - 1) {
                            all_vars_str = all_vars_str.substr(0, all_vars_str.length() - 1);
                            all_vars_str +=" или " + to_string(all_turn_option[i]);
                        }
                        else {all_vars_str += to_string(all_turn_option[i]) + ", ";}
                    }
                    cout << "Вы не можете забрать столько палочек! Выберете один из вариантов - " + all_vars_str << '\n';
                    num = -1;
                }
            }
        }
        else {
            usleep(1000000);
            int bot_chose = rand()/(double)RAND_MAX * size_turns;
            num = all_turn_option[bot_chose];
            print_with_sleep(to_string(num) +  "\n");
            turn(all_sticks,num,bot);
            winner = player;

        }
        // change on like - check who`s turn and do it
        turns_cnt += 1;
        first_turn += 1;
    }

    return winner;

}
void start_champ_with_bot(
    int all_turn_option[],
    int size_turns,
    int one_win_score = 15,
    int all_sticks = 21,
    int start_players_score = 100

    ){

    string p1 = "Player";
    string p2 = "Bot";
    int games_cnt = 0;
    int p1_score = start_players_score;
    int p2_score = start_players_score;

    cout << RULES;

    while (p1_score > 0  && p2_score > 0) {
        print_with_sleep(format("Количество очков:\n {} - {}\n {} - {}\n", p1, p1_score,p2, p2_score));
        games_cnt++;
        print_with_sleep(format("Игра - {}\n", games_cnt));
        int first_turn = (double)rand()/RAND_MAX ;
        string winner = game_with_bot(all_turn_option, size_turns,all_sticks,p2_score);
        print_with_sleep(format("Победитель {} раунда -  {}!\n", games_cnt,winner ));
        if (winner == p1) {
            p2_score -= one_win_score;
        }
        else if (winner == p2) {
            p1_score -= one_win_score;
        }
        else {1/0;}
    }
    print_with_sleep("Игра окончена!\n");
    if (p1_score <= 0) {
        print_with_sleep(format("Победил {}", p2));
    } else {
        print_with_sleep(format("Победил {}", p1));
    }

}


int main() {

    int turns_options[] = {1, 2, 3};
    while (true) {
        cout << "Введите start что бы начать игру, или ex - что для выхода\n";
        string choise;
        cin >> choise;
        if (choise == "start") {
            start_champ_with_bot(turns_options,3,15,21,100);
        }
        else if (choise == "ex") {
            cout << "Произвожу выход!\n";
            break;

        } else {
            cout << "Хмм... такого варианта нет, попробуйте еще раз\n";

        }
    }

}
