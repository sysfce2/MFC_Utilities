#include "stdafx.h"
#include "IGridController.h"

void IGridController::DoInitialUpdate(int num_rows)
{
	grid.SetRowCount(num_rows + 1);
	grid.SetColumnCount(count_columns);
	grid.SetFixedRowCount();
	grid.SetFixedColumnCount();
	grid.SetHeaderSort(true);
	grid.SetSingleRowSelection(true);

	FillHeaders();

	RefreshGrid();

	AutoSizeColumns();
}

void IGridController::AutoSizeColumns()
{
	for (int i = 0; i < count_columns; ++i)
	{
		grid.AutoSizeColumn(i);
	}
}

void IGridController::FillGrid(int num_rows)
{
	for (int i = 0; i < num_rows; ++i)
	{
		FillLine(i);
	}
}
