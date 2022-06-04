#include <iostream>
#include<vector>
#include<fstream>

/*
地面　1
建物　2
*/
int main()
{
	std::vector<std::vector<double>> points(925, std::vector<double>(1132));
	//points.at(y座標).at(x座標)
	int i = 0;
	int xrange = 1132;
	int yrange = 925;
	std::ifstream ifs("MapdataGL.dat");
	std::ofstream ofs("MapdataGLl.dat");
	double c;
	double a, b;
	int ad, bd;

	if (ifs.fail()) {
		std::cout << "入力ファイルをオープンできません\n";
		return 1;
	}
	if (ofs.fail()) {
		std::cout << "出力ファイルをオープンできません\n";
		return 1;
	}

	while ((ifs >> a >> b >> c)) {
		ad = a;
		bd = b;
		points.at(bd + 33277).at(ad + 7540) = c;
	}

	//ラベル追加(地面データでは地面ラベルをx座標 y座標 z座標 1のように追加、建物データでは建物ラベルをx座標 y座標 z座標 2のように追加)
	for (i = 0; i < xrange; i++) {
		for (int j = 0; j < yrange; j++) {
			double x = i - 7540;
			double y = j - 33277;
			if (points.at(j).at(i) != 0) {
				ofs << x << " " << y << " " << points.at(j).at(i) << " " << 1 << "\n";
			}
		}
	}
	return 0;
}