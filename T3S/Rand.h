#pragma once
class Rand
{
public:
	static int cnt;
	static void checkSeed();
	static void newSeed(int s);
	static int randi();
	static int randi(int max);
};

