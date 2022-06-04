#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>

int main()
{
	std::vector<std::vector<double>> points(925, std::vector<double>(1132));
	std::vector <std::vector<double>> judges(925, std::vector<double>(1132));
	//points.at(y座標).at(x座標)
	std::vector<std::vector<double>> light(925, std::vector<double>(1132));
	int i, j;
	int xrange = 1132;
	int yrange = 925;
	std::ifstream ifs("MapdataG.dat");
	std::ofstream ofs("MapdataGL.dat");
	double c;
	double a, b;
	int ad, bd;
	double dis = 4.0; //削減する点を判定するときのまわりの点との高さの差

	while ((ifs >> a >> b >> c)) {
		ad = a;
		bd = b;
		points.at(bd + 33277).at(ad + 7540) = c;
	}
	for (i = 0; i < xrange; i++) {
		for (int j = 0; j < yrange; j++) {
			if (points.at(j).at(i) != 0) {
				judges.at(j).at(i) = 0;
			}
			else if (points.at(j).at(i) == 0) {
				judges.at(j).at(i) = -1;
			}
		}
	}

	for (i = 1; i < 1131; i++) {
		for (j = 1; j < 924; j++) {
			if (judges.at(j).at(i) != -1) {
				if (std::fabs(points.at(j).at(i) - points.at(j + 1).at(i)) < dis && std::fabs(points.at(j).at(i) - points.at(j).at(i + 1)) < dis && std::fabs(points.at(j).at(i) - points.at(j + 1).at(i + 1)) < dis) {
					judges.at(j + 1).at(i) = -1;
					judges.at(j + 1).at(i + 1) = -1;
					judges.at(j).at(i + 1) = -1;
					points.at(j).at(i) = (points.at(j + 1).at(i + 1) + points.at(j + 1).at(i) + points.at(j).at(i + 1) + points.at(j).at(i)) / 4.0;
					points.at(j + 1).at(i + 1) = 0;
					points.at(j + 1).at(i) = 0;
					points.at(j).at(i + 1) = 0;
				}
			}
		}
	}

	for (j = 0; j < yrange; j++) {
		for (int i = 0; i < xrange; i++) {
			if (points.at(j).at(i) != 0) {
					double x = i - 7540.0;
					double y = j - 33277.0;
					ofs << x << " " << y << " " << points.at(j).at(i) << "\n";
			}
		}
	}
	return 0;
}

