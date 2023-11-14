﻿#include <cstdio>
#include <iostream>
#include "Player.h"
#include "Dealer.h"
#include "Shoe.h"
#define DEBUG
using namespace std;

const char* CARD_NUMBER[] = { "  ", " A", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K" };
const char* CARD_SUIT[] = { "  heart", "diamond", "  spade", "   club" };

void Deal(CPlayer& cPlayer, CDealer& cDealer, CShoe& cShoe);
void Player(CPlayer& cPlayer, CShoe& cShoe);
void Dealer(CDealer& cDealer, CShoe& cShoe);
void Result(CPlayer cPlayer, CDealer cDealer);

int main(){
	CShoe cShoe;
	CPlayer cPlayer;
	CDealer cDealer;

#ifdef DEBUG
	cShoe.Show_cradShoe();
	printf("\n");
#endif // DEBUG

	// ディール
	Deal(cPlayer, cDealer, cShoe);

#ifdef DEBUG
	printf("\n");
	cShoe.Show_cradShoe();
	printf("\n");
#endif // DEBUG

	// プレイヤ
	printf("\n----- プレイヤのターン -----\n");
	Player(cPlayer, cShoe);

	// ディーラー
	printf("\n---- ディーラーのターン ----\n");
	Dealer(cDealer, cShoe);

	// 勝利判定
	Result(cPlayer, cDealer);

#ifdef DEBUG
	printf("\n");
	cShoe.Show_cradShoe();
	printf("\n");
#endif // DEBUG

	return 0;
}

void Deal(CPlayer& cPlayer, CDealer& cDealer, CShoe& cShoe) {
	printf("--------- ディール ---------\n");
	// 初手ディーラー
	cDealer.Hit_card(cShoe, 2);
	// アップカード
	printf("アップカード\n");
	printf("num:%s, suit:%s\n", CARD_NUMBER[cDealer.UpCard().cardNum], CARD_SUIT[cDealer.UpCard().cardSuit]);
	// スコア表示
	printf("Score:%s + a\n\n", CARD_NUMBER[cDealer.UpCard().cardNum]);

	// 初手プレイヤ
	cPlayer.Hit_card(cShoe, 2);
	// 手札表示
	printf("プレイヤ手札\n");
	cPlayer.ShowHand();
	// スコア表示
	printf("Score:%d\n", cPlayer.SumScore());
	printf("\n");
}

void Player(CPlayer& cPlayer, CShoe& cShoe) {
	int select = 0;

	do {
		printf("1 > スタンド\n2 > ヒット\n> ");
		cin >> select;
		if (select == 2) {
			printf("ヒット\n");
			cPlayer.Hit_card(cShoe);
		}
		cPlayer.ShowHand();
		printf("Score:%d\n", cPlayer.SumScore());
		if (cPlayer.SumScore() > 21) {
			printf("バースト\n");
		}
	} while (select != 1 && cPlayer.SumScore() <= 21);
}

void Dealer(CDealer& cDealer, CShoe& cShoe) {
	cDealer.ShowHand();
	printf("Score:%d\n", cDealer.SumScore());
	while (cDealer.SumScore() < 17) {
		cDealer.Hit_card(cShoe);
		cDealer.ShowHand();
		printf("Score:%d\n", cDealer.SumScore());
		if (cDealer.SumScore() > 21) {
			printf("バースト\n");
		}
	}
}

void Result(CPlayer cPlayer, CDealer cDealer) {
	printf("\n---------- 勝　敗 ----------\n");
	if (cPlayer.SumScore() > 21) {
		printf("ディーラーの勝利\n");
	}
	else if (cDealer.SumScore() > 21) {
		printf("プレイヤの勝利\n");
	}
	else if (cPlayer.SumScore() > cDealer.SumScore()) {
		printf("プレイヤの勝利\n");
	}
	else if (cDealer.SumScore() > cPlayer.SumScore()) {
		printf("ディーラーの勝利\n");
	}
	else {
		printf("プッシュ\n");
	}
}