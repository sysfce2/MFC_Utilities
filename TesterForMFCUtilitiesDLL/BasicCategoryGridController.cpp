#include "stdafx.h"

#include "BasicCategoryGridController.h"



using namespace sqlite_orm;


void BasicCategoryGridController::OnInitialUpdate()
{
	lines = ORM::Storage::getStorage().get_all<Model::Category>(order_by(&Model::Category::m_name_id));
	DoInitialUpdate(lines.size());
	grid.m_sortingFunctions = { JD::Comparison::Text, JD::Comparison::Text };
}

void BasicCategoryGridController::RefreshGrid()
{
	FillGrid( lines.size());
}

void BasicCategoryGridController::OnGridClick(NMHDR * pNotifyStruct)
{
	NM_GRIDVIEW* pItem = reinterpret_cast<NM_GRIDVIEW*>(pNotifyStruct);
	TRACE(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	if (pItem->hdr.idFrom == grid.GetDlgCtrlID())
	{
		//pItem->hdr.hwndFrom;
		
	}
}

void BasicCategoryGridController::FillHeaders()
{
	grid.SetItemText(0, Columns::NAME, L"CATEGORY NAME");
	grid.SetItemText(0, Columns::REAL, L"REAL?");
}

void BasicCategoryGridController::FillLine(int row)
{
	auto line = lines[row];

	auto txt = JD::to_cstring(line.m_name_id);
	grid.SetItemText(row + 1, Columns::NAME, txt);
	auto boolVal = JD::to_cstring(line.m_real_expense_or_income ? "Real" : "Not real");
	grid.SetItemText(row + 1, Columns::REAL, boolVal);

}