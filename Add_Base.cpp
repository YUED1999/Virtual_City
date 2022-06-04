#include <iostream>
#include<vector>
#include<fstream>

int main()
{
	std::vector<std::vector<double>> points(925, std::vector<double>(1132));
	//points.at(y座標).at(x座標)
	std::vector<std::vector<double>> label(925, std::vector<double>(1132));
	int i = 0;
	int xrange = 1132;
	int yrange = 925;
	std::ifstream ifs("MapdataBGLl.dat");
	std::ofstream ofs("MapdataBGLla.dat");
	double c;
	double a, b;
	int ad, bd;
	int d;

	if (ifs.fail()) {
		std::cout << "入力ファイルをオープンできません\n";
		return 1;
	}
	if (ofs.fail()) {
		std::cout << "出力ファイルをオープンできません\n";
		return 1;
	}

	while ((ifs >> a >> b >> c >> d)) {
		ad = a;
		bd = b;
		points.at(bd + 33277).at(ad + 7540) = c;
		label.at(bd + 33277).at(ad + 7540) = d;
	}

	for (i = 1; i < xrange-1; i++) {
		for (int j = 1; j < yrange-1; j++) {
			double x = i;
			double y = j;
			if (points.at(j).at(i) != 0) {
				ofs << x << " " << y << " " << points.at(j).at(i) << " " << label.at(j).at(i) << "\n";
			}
		}
	}
	ofs << 0 << " " << 0 << " " << -80 << " " << 0 << "\n";
	ofs << 0 << " " << 924 << " " << -80 << " "  << 0 << "\n";
	ofs << 1131 << " "  << 0 << " " << -80 << " " << 0 << "\n";
	ofs << 1131 << " " << 924 << " " << -80 << " " << 0 << "\n";
	return 0;
}