#include "Decimal.h"
Decimal::Decimal(string a) :number(a)//�~��//�S���R�W��Decimal(�i�H������
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡
	if (space != a.npos) /*a���⦡�A�ݭn�p��*/
	{
		////////////////////////////////
		//a=number�p��(a);
		////////////////////////////////
		vector<string> formula;//�x�s�⦡��
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��A�x�s�iformula
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
		if (Valid == false)//��J�Ʀr�˴����ųW�w
		{
			num = "0";
			name = "";
		}
		else//�⦡�p��
		{
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0])) //�p�GCompute�ᵲ�G�ëD�Ʀr�A�Ĥ@��s���O���~�T��
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else //�x�s�p�⵲�G
			{
				//�p�G���G����ơA�ন�p��//
				long long int dpit = formula[0].find(".");/*�M��p�⵲�G���p���I*/
				if (dpit == formula[0].npos) { /*�p�G�p�⵲�G����ơA�ɤp���I�M�p���I��100��*/
					formula[0].insert(formula[0].end(), 0, '.');
					formula[0].insert(formula[0].end(), 100, '0');
				}
				else {/*�p�G���G���p�ơA�^�ǵ��G���ӷ|��p���I��100��A�N���ݭn�o�@�qelse*/
					formula[0].insert(formula[0].end(), 100-(formula[0].length()-1-dpit), '0');
				}
				Decimal temp(formula[0]);//�⵪�װ��r��B�z
				num = temp.num;
				name = "";
			}
		}
	}
	else { //��@�Ʀr���έp��
		string tempPN = "";
		if (a[0] == '-') //����t���M�Ʀr����
		{
			tempPN = "-"; /*�x�s�t����tempPN*/
			a = a.substr(1, a.length() - 1);/*�h���t���A�]�i�H��erase?*/
		}
		long long int ait = a.find("."); /*�M��a���p���I��m*/
		if (ait == a.npos) { /*�p�G�p�⵲�G����ơA�ɤp���I�M�p���I��100��*/
			a.insert(a.end(), 0, '.');
			a.insert(a.end(), 100, '0');
			ait = a.find("."); /*���s�M��a���p���I��m*/
		}
		else { /*�p�G���G���p�ơA��0�ɺ��p���I��100��*/
			a.insert(a.end(), 100 - (a.length() - 1 - ait), '0');
		}
		while (a[0] == '0' && ait > 1) /*dpit�۷���Ʀ�ơA��dpit�j��1�ɡA�ˬd�O�_���h�l��0*/
			a = a.substr(1, a.length() - 1); /*�h���h�l��0*/
		tempPN += a; /*a��z�����x�s�itempPN*/
		num = tempPN;
		name = "";
	}
}

Decimal::Decimal(string a, string setN) :number(a)//���R�W��Decimal
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡
	if (space != a.npos) /*a���⦡�A�ݭn�p��*/
	{
		////////////////////////////////
		//a=number�p��(a);
		////////////////////////////////
		vector<string> formula;//�x�s�⦡��
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
		if (Valid == false)//��J�Ʀr�˴����ųW�w
		{
			num = "0";
			name = "";
		}
		else//�⦡�p��
		{
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0]))//�Ĥ@��s���O���~�T��
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else//�p�⵲�G�x�s
			{
				//�p�G���G����ơA�ন�p��//
				long long int dpit = formula[0].find(".");/*�M��p�⵲�G���p���I*/
				if (dpit == formula[0].npos) { /*�p�G�p�⵲�G����ơA�ɤp���I�M�p���I��100��*/
					formula[0].insert(formula[0].end(), 0, '.');
					formula[0].insert(formula[0].end(), 100, '0');
				}
				else {/*�p�G���G���p�ơA�^�ǵ��G���ӷ|��p���I��100��A�N���ݭn�o�@�qelse*/
					formula[0].insert(formula[0].end(), 100 - (formula[0].length() - 1 - dpit), '0');
				}
				Decimal temp(formula[0]);//�⵪�װ��r��B�z
				num = temp.num;
				name = setN;
				numDecList.push_back(num);
				nameDecList.push_back(name);
			}
		}
	}
	else //��@�Ʀr���έp��
	{
		string tempPN = "";
		if (a[0] == '-')//����t���M�Ʀr����
		{
			tempPN = "-"; /*�x�s�t����tempPN*/
			a = a.substr(1, a.length() - 1); /*�h���t��*/
		}
		long long int ait = a.find("."); /*�M��a���p���I��m*/
		if (ait == a.npos) { /*�p�G�p�⵲�G����ơA�ɤp���I�M�p���I��100��*/
			a.insert(a.end(), 0, '.');
			a.insert(a.end(), 100, '0');
			ait = a.find("."); /*���s�M��a���p���I��m*/
		}
		else { /*�p�G���G���p�ơA��0�ɺ��p���I��100��*/
			a.insert(a.end(), 100 - (a.length() - 1 - ait), '0');
		}
		while (a[0] == '0' && ait > 1) /*dpit�۷���Ʀ�ơA��dpit�j��1�ɡA�ˬd�O�_���h�l��0*/
			a = a.substr(1, a.length() - 1); /*�h���h�l��0*/
		num = tempPN;
		name = setN;
		numDecList.push_back(num);
		nameDecList.push_back(name);
	}
}
Decimal Decimal::operator =(string a)/////////////a�O�Ʀr�A����Ǩ�L�ܼƦW�r�i��(��¥Ψӭק�this����
{
	if (this->name != "") {/*�p�Gthis���W�r*/
		int pos = searchDecName(this->name);/*�d��nameDecList���O�_��this���W�r�A�P�B�ק�static����*/
		Decimal temp(a); /*����Ʀr���B�z(�h�e�m0)�A�Oa�ŦXDecimal�榡*/
		this->numDec = temp.numDec;/*����temp���Ʀr(a)��this�A�]�N�O�ק�this���ƭ�*/
		numDecList[pos] = this->numDec;/*�p�Gthis���W�r�s�b�A�ק�pos��m���ƭ�*/
	}
	return *this;
}

Decimal Decimal::operator =(const Decimal& var)//var�O�ܼ�(this���ƭȩM�W�r����
{
	if (this->name != "") { /*�p�Gthis���W�r*/
		int pos = searchDecName(this->name);/*�d��nameDecList���O�_��this���W�r�A�P�B�ק�static����*/
		nameDecList[pos] = var.name;/*�ק�pos��m���W�r*/
		numDecList[pos] = var.numDec;/*�ק�pos��m���ƭ�*/
		this->numDec = var.numDec;/*�ק�this���W�r*/
		this->name = var.name;/*�ק�this���ƭ�*/
	}
	return *this;
}

ostream& operator<<(ostream& strm, const Decimal& c)
{
	strm << c.numDec;
	return strm;
}

istream& operator>>(istream& strm, Decimal& c)
{
	string temp;//////////////��Jtemp�O�Ʀr
	strm >> temp;//��Jtemp�s�JDec
	c = temp;//assign=
	return strm;
}

int Decimal::searchDecName(string a)//��W�r�s���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
{
	for (int i = 0; i < nameDecList.size(); i++)
	{
		if (a == nameDecList[i])
			return i;
	}
	return -1;//�S���
}

string Decimal::searchDecValue(int pos)//�^�ǦW�r���ȡApos=-1�^��WRONG_NAME
{
	if (pos == -1)
		return "WRONG_NAME";
	return numDecList[pos];
}

void Decimal::setValue(string value, int pos)
{
	numDecList[pos] = value;
}