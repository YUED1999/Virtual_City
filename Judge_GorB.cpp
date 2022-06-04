#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>

struct GPoint {
	int x;
	int y;
	double z;
};

int main()
{
	std::vector<std::vector<double>> points(925, std::vector<double>(1132));
	//points.at(y座標).at(x座標)
	std::vector<std::vector<double>> gorb(925, std::vector<double>(1132));
	int i = 0, j;
	int xrange = 1132;
	int yrange = 925;
	std::ifstream ifs("NMD.dat");
	std::ofstream gfs("MapdataG.dat");
	std::ofstream bfs("MapdataB.dat");
	double c;
	double a, b;
	int ad, bd;
	std::vector<int> high{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//最初の仮の地面の点
	struct GPoint sgp1;
	double d1 = 2.5; //地面から見た上の幅
	double d4 = 2.5; //建物から見た下の幅
	double bdis = 20.0; //建物→地面と判定されたとき、最頻値+bdisより高い点なら建物に修正
	double dis = 0.5; //判定修正の際の差

	while ((ifs >> a >> b >> c)) {
		ad = a;
		bd = b;
		points.at(bd + 33277).at(ad + 7540) = c;
		i++;
	}
	//gorbの初期化
	for (i = 0; i < xrange; i++) {
		for (int j = 0; j < yrange; j++) {
			if (points.at(j).at(i) != 0) {
				gorb.at(j).at(i) = 0;
			}
			else if (points.at(j).at(i) == 0) {
				gorb.at(j).at(i) = -1;
				//存在しない点のgorbは-1
			}
		}
	}

	//全体の最頻値を取得
	for (i = 0; i < 1132; i++) {
		for (int j = 0; j < 925; j++) {
			if (points.at(j).at(i) != 0) {
				for (int k = 0; k < 20; k++) {
					if (points.at(j).at(i) > k&& points.at(j).at(i) <= k + 1.0) {
						high[k]++;
					}
				}
			}
		}
	}
	std::vector<int>::iterator iter = std::max_element(high.begin(), high.end());
	int mode = std::distance(high.begin(), iter);
	for (i = 500; i < 1131; i++) {
		int judge = 0;
		for (j = 300; j < 924; j++) {
			if (points.at(j).at(i) > mode&& points.at(j).at(i) <= mode + 1.0) {
				sgp1.x = i;
				sgp1.y = j;
				sgp1.z = points.at(j).at(i);
				gorb.at(j).at(i) = 1;
				judge = 1;
				break;
			}
		}
		if (judge == 1) {
			break;
		}
	}

	i = sgp1.x;
	j = sgp1.y;
	while (1) {
		//初期点から下一列の走査
		int jplus = j + 1;
		if (jplus == 925 || points.at(jplus).at(i) == 0) {
			break;
		}
		else {
			if (points.at(jplus).at(i) <= points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
				//地面→地面と判定
				gorb.at(jplus).at(i) = 1;
			}
			else if (points.at(jplus).at(i) > points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
				//地面→建物と判定
				gorb.at(jplus).at(i) = 2;
			}
			else if (points.at(jplus).at(i) >= points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
				//建物→建物と判定
				gorb.at(jplus).at(i) = 2;
			}
			else if (points.at(jplus).at(i) < points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
				//建物→地面と判定
				gorb.at(jplus).at(i) = 1;

				if (points.at(jplus).at(i) > sgp1.z + bdis) {
					gorb.at(jplus).at(i) = 2;
				}
			}
			else {
				gorb.at(jplus).at(i) = 1;
			}
			j++;
		}
	}
	i = sgp1.x;
	j = sgp1.y;
	while (1) {
		//初期点から上一列の走査
		int jminus = j - 1;
		if (jminus == -1 || points.at(jminus).at(i) == 0) {
			break;
		}
		else {
			if (points.at(jminus).at(i) <= points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
				//地面→地面
				gorb.at(jminus).at(i) = 1;
			}
			else if (points.at(jminus).at(i) > points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
				//地面→建物
				gorb.at(jminus).at(i) = 2;
			}
			else if (points.at(jminus).at(i) >= points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
				//建物→建物
				gorb.at(jminus).at(i) = 2;
			}
			else if (points.at(jminus).at(i) < points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
				//建物→地面
				gorb.at(jminus).at(i) = 1;

				if (points.at(jminus).at(i) > sgp1.z + bdis) {
					gorb.at(jminus).at(i) = 2;
				}
			}
			else {
				gorb.at(jminus).at(i) = 1;
			}
			j--;
		}
	}

	i = sgp1.x;
	for (j = 0; j < 925; j++) {
		//初期点の列の右一行と左一行の走査
		i = sgp1.x;
		if (points.at(j).at(i) == 0) {

		}
		else {
			i = sgp1.x;
			while (1) {
				int iplus = i + 1;
				if (iplus == 1132 || points.at(j).at(iplus) == 0) {
					break;
				}
				else {
					if (points.at(j).at(iplus) <= points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
						//地面→地面
						gorb.at(j).at(iplus) = 1;
					}
					else if (points.at(j).at(iplus) > points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
						//地面→建物
						gorb.at(j).at(iplus) = 2;
					}
					else if (points.at(j).at(iplus) >= points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
						//建物→建物
						gorb.at(j).at(iplus) = 2;
					}
					else if (points.at(j).at(iplus) < points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
						//建物→地面
						gorb.at(j).at(iplus) = 1;

						if (points.at(j).at(iplus) > sgp1.z + bdis) {
							gorb.at(j).at(iplus) = 2;
						}
					}
					else {
						gorb.at(j).at(iplus) = 1;
					}
					i++;
				}
			}
			i = sgp1.x;
			while (1) {
				int iminus = i - 1;
				if (iminus == -1 || points.at(j).at(iminus) == 0) {
					break;
				}
				else {
					if (points.at(j).at(iminus) <= points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
						//地面→地面
						gorb.at(j).at(iminus) = 1;
					}
					else if (points.at(j).at(iminus) > points.at(j).at(i) + d1 && gorb.at(j).at(i) == 1) {
						//地面→建物
						gorb.at(j).at(iminus) = 2;
					}
					else if (points.at(j).at(iminus) >= points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
						//建物→建物
						gorb.at(j).at(iminus) = 2;
					}
					else if (points.at(j).at(iminus) < points.at(j).at(i) - d4 && gorb.at(j).at(i) == 2) {
						//建物→地面
						gorb.at(j).at(iminus) = 1;

						if (points.at(j).at(iminus) > sgp1.z + bdis) {
							gorb.at(j).at(iminus) = 2;
						}
					}
					else {
						gorb.at(j).at(iminus) = 1;
					}
					i--;
				}
			}
		}
	}



	for (i = 0; i < xrange; i++) {
		for (j = 0; j < yrange; j++) {
			int jplus = j + 1;
			if (jplus == 925 || points.at(jplus).at(i) == 0) {
				break;
			}
			if (points.at(jplus).at(i) != 0 && gorb.at(j).at(i) == 1) {
				if (std::fabs(points.at(jplus).at(i) - points.at(j).at(i)) < 1.0) {
					gorb.at(jplus).at(i) = 1;
				}
			}
		}
	}


	for (j = 0; j < yrange; j++) {
		for (int i = 0; i < xrange; i++) {
			if (gorb.at(j).at(i) == 1) {
				double x = i - 7540.0;
				double y = j - 33277.0;
				if (points.at(j).at(i) != 0) {
					gfs << x << " " << y << " " << points.at(j).at(i) << "\n";
				}
			}
			else if (gorb.at(j).at(i) == 2) {
				double x = i - 7540.0;
				double y = j - 33277.0;
				if (points.at(j).at(i) != 0) {
					bfs << x << " " << y << " " << points.at(j).at(i) << "\n";
				}
			}
		}
	}
	return 0;
}