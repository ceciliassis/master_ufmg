#include <iostream>
#include <cstdio>

using namespace std;

int profit(int *profitByDay, int &cost, int n) {
	if (n == 1) {
		int p = profitByDay[0] - cost;
		if (p < 0)
			return 0;
		return p;
	}

	int resp = profit(profitByDay, cost, n - 1);
	int currentProfit = 0;
	for(int i = n - 1; i > -1;  i--) {
		currentProfit += (profitByDay[i] - cost);
		if (currentProfit > resp)
            resp = currentProfit;
	}

	return resp;
}

int main() {
	int days, cost;

	while (scanf("%d", &days) != EOF)
	{
		scanf("%d", &cost);
		int profitByDay[days];
		for(int i = 0; i < days; i++)
			scanf("%d", &profitByDay[i]);

		printf("%d\n", profit(profitByDay, cost, days) );
	}

	printf("\n");
	return 0;
}
