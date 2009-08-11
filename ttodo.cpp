#include "ttodo.h"
#include "task.h"

TTodo::TTodo()
{
}

void TTodo::setPercentComplete(int comp)
{
	m_complete = comp;
}
void TTodo::setComplete(bool comp)
{
	if (comp) {
		m_complete = 100;
	} else {
		m_complete = 0;
	}
}

int TTodo::getPercentComplete()
{
	return m_complete;
}
bool TTodo::isComplete()
{
	if (m_complete == 100) {
		return true;
	}
	return false;
}
