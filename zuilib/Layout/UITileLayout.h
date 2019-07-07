#ifndef __UITILELAYOUT_H__
#define __UITILELAYOUT_H__

#pragma once

namespace zuilib {

	class ZUILIB_API CTileLayoutUI : public CContainerUI
	{
	public:
		CTileLayoutUI();

		LPCWSTR GetClass() const;
		LPVOID GetInterface(LPCWSTR pstrName);

		void SetPos(RECT rc, bool bNeedInvalidate = true);

		int GetFixedColumns() const;
		void SetFixedColumns(int iColums);
		int GetFixedRows() const;
		void SetFixedRows(int iColums);
		int GetChildVPadding() const;
		void SetChildVPadding(int iPadding);

		SIZE GetItemSize() const;
		void SetItemSize(SIZE szSize);
		int GetColumns() const;
		int GetRows() const;
		void SetAttribute(LPCWSTR pstrName, LPCWSTR pstrValue);
		bool Add(CControlUI* pControl);
		bool AddAt(CControlUI* pControl, int iIndex);

	protected:
		SIZE m_szItem;
		int m_nColumns;
		int m_nRows;

		int m_nColumnsFixed;
		int m_nRowsFixed;
		int m_iChildVPadding;
		bool m_bIgnoreItemPadding;
	};
}
#endif // __UITILELAYOUT_H__
