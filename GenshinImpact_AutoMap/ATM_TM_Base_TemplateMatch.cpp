#include "ATM_TM_Base_TemplateMatch.h"

void ATM_TM_Base_TemplateMatch::setLeftMat(Mat leftMat)
{
	_leftMat = leftMat;
}
void ATM_TM_Base_TemplateMatch::setRightMat(Mat rightMat)
{
	_rightMat = rightMat;
}
bool ATM_TM_Base_TemplateMatch::Match(int method, InputArray mask)
{
	if (_leftMat.empty() || _rightMat.empty())
	{
		throw("��ͼ������ͼΪ�գ�");
		//return false;
	}
	if (_leftMat.channels() != _rightMat.channels())
	{
		throw("��ͼ����ͼ��ͨ������ͬ��");
		//return false;
	}
	if (_leftMat.rows > _rightMat.rows || _leftMat.cols > _rightMat.cols)
	{
		throw("��ͼ�ĳ���������ͼ��");
		//return false;
	}

	matchTemplate(_leftMat, _rightMat, tmp, method, mask);
	minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
	return true;
}
//bool ATM_TM_Base_TemplateMatch::Match()
//{
//	return Match(TM_CCOEFF_NORMED);
//}