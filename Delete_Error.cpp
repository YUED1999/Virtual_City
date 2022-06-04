
#include <iostream>
#include<vector>
#include<fstream>

int main()
{
	std::vector<std::vector<double>> points(925, std::vector<double>(1132));
	//points.at(y座標).at(x座標)
	int i = 0;
	int imax;
	int xrange = 1132;
	int yrange = 925;
	std::ifstream ifs("Korakuen.dat");
	std::ofstream ofs("NMD.dat");
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
		i++;
	}
	imax = i;

	for (i = 0; i < xrange; i++) {
		for (int j = 0; j < yrange; j++) {
			if (points.at(j).at(i) < 0) {
				double sum = 0;
				int cnt = 0;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						if ((j - 1 + k >= 0 && j - 1 + k < 925) && (i - 1 + l >= 0 && i - 1 + l < 1132)) {
							if (points.at(j - 1 + k).at(i - 1 + l) > 0) {
								sum += points.at(j - 1 + k).at(i - 1 + l);
								cnt++;
							}
						}
						
					}
				}
				points.at(j).at(i) = sum / cnt;
			}
		}
	}
	for (i = 1; i < 1131; i++) {
		for (int j = 1; j < 924; j++) {
			if (points.at(j).at(i) == 0) {
				double sum = 0;
				int cnt = 0;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						if ((j - 1 + k >= 0 && j - 1 + k < 925) && (i - 1 + l >= 0 && i - 1 + l < 1132)) {
							if (points.at(j - 1 + k).at(i - 1 + l) > 0) {
								sum += points.at(j - 1 + k).at(i - 1 + l);
								cnt++;
							}
						}

					}
				}
				points.at(j).at(i) = sum / cnt;
			}
		}
	}

	for (i = 0; i < xrange; i++) {
		for (int j = 0; j < yrange; j++) {
			double x = i - 7540;
			double y = j - 33277;
			if (points.at(j).at(i) != 0) {
				ofs << x << " " << y << " " << points.at(j).at(i) << "\n";
			}
		}
	}
	return 0;
}

