#include "ttodo.h"
#include "task.h"

#include <QString>

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

QString TTodo::toString()
{
	QString out = Task::toString();
	QString todoOut = QString("\n\tComplete: %1")
			.arg(getPercentComplete());
	out.append(todoOut);
	return out;
}
