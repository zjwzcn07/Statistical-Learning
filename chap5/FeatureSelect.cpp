#pragma once
#include "FeatureSelect.h"


FeatureSelect::FeatureSelect()
{
}

FeatureSelect::FeatureSelect(vector<vector<int>>&_data, vector<int>&_kind,vector<string>&_name)
{
	data = _data;
	kind = _kind;
	name = _name;
}

FeatureSelect::~FeatureSelect()
{
}

void FeatureSelect::Statistics()
{
	try
	{
		//计算经验熵
		int data_num = kind.size();
		assert(data_num);
		map<int, double>count_kind;
		count_kind.clear();
		for (auto k : kind)
			count_kind[k] += 1.0;
		//所有实例属于同一类，则将类Ck返回
		if (count_kind.size() == 1)
		{
			only_one_Ck.first = 1;
			only_one_Ck.second = (*count_kind.begin()).first;
			return;
		}
		//统计实例数最大的类Ck
		int num_kind = 0;
		for (auto k : count_kind)
		{
			if (k.second > num_kind)
			{
				num_kind = k.second;
				max_kind = k.first;
			}
		}
		for (auto ck : count_kind)
		{
			double ckd = ck.second / data_num;
			empirical_entropy -= ckd*log2(ckd);
		}
		//计算经验条件熵
		int eigen_number = data.front().size();
		//没有特征值，则将实例数最大的类Ck返回
		if (eigen_number == 0)
		{
			no_feature = 1;
			return;
		}
		for (int i = 0;i != eigen_number;++i)
		{
			feature.push_back(vector<int>());
			for (int j = 0;j != data_num;++j)
			{
				feature[i].push_back(data[j][i]);
			}
		}
		//计算增益
		double max_gain = (double)INT_MIN;
		for (int i = 0;i != eigen_number;++i)
		{
			conditional_entropy.push_back(0);
			double hda = 0;
			count_kind.clear();
			for (auto k : feature[i])
				count_kind[k] += 1.0;
			map<int, map<int, double>>Dik;
			Dik.clear();
			for (int j = 0;j != data_num;++j)
			{
				int ii = feature[i][j];
				int kk = kind[j];
				Dik[ii][kk] += 1.0;
				feature_value[i].insert(ii);
			}
			for (auto D : count_kind)
			{
				int Di_num = D.second;
				double di_div_d = Di_num / (double)data_num;
				map<int, double>tmpDik = Dik[D.first];
				double tmp_sum = 0;
				for (auto dik : tmpDik)
				{
					double p = dik.second / Di_num;
					tmp_sum += (p*log2(p));
				}
				conditional_entropy[i] -= di_div_d*tmp_sum;
			}
			gain.push_back(empirical_entropy - conditional_entropy[i]);
			if (max_gain < gain[i])
			{
				max_gain = gain[i];
				max_gain_kind = i;
			}
			gain_ratio.push_back(gain[i] / empirical_entropy);
		}

	}
	catch (const std::exception&)
	{
		cout << "data empty" << endl;
	}
}