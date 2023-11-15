
// MFCApplication 20190814View.cpp: CMFCApplication20190814View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication 20190814.h"
#endif

#include "MFCApplication 20190814Doc.h"
#include "MFCApplication 20190814View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication20190814View

IMPLEMENT_DYNCREATE(CMFCApplication20190814View, CScrollView)

BEGIN_MESSAGE_MAP(CMFCApplication20190814View, CScrollView)
	ON_COMMAND(PixelAdd, &CMFCApplication20190814View::OnPixeladd)
	ON_COMMAND(PixelMUL, &CMFCApplication20190814View::OnPixelmul)
	ON_COMMAND(PixelSUB, &CMFCApplication20190814View::OnPixelsub)
	ON_COMMAND(PixelDIV, &CMFCApplication20190814View::OnPixeldiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CMFCApplication20190814View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CMFCApplication20190814View::OnPixelContrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CMFCApplication20190814View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CMFCApplication20190814View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CMFCApplication20190814View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SMOOTHING, &CMFCApplication20190814View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_SHARPENING, &CMFCApplication20190814View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_EMBOSSING, &CMFCApplication20190814View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CMFCApplication20190814View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CMFCApplication20190814View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CMFCApplication20190814View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CMFCApplication20190814View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CMFCApplication20190814View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CMFCApplication20190814View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CMFCApplication20190814View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CMFCApplication20190814View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CMFCApplication20190814View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CMFCApplication20190814View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CMFCApplication20190814View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CMFCApplication20190814View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CMFCApplication20190814View::OnGeometryZoominBilinearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CMFCApplication20190814View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CMFCApplication20190814View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CMFCApplication20190814View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CMFCApplication20190814View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_HOLIZANTIAL_FUP, &CMFCApplication20190814View::OnGeometryHolizantialFup)
	ON_COMMAND(ID_GEOMETRY_VERTICAL_FUP, &CMFCApplication20190814View::OnGeometryVerticalFup)
END_MESSAGE_MAP()

// CMFCApplication20190814View 생성/소멸

CMFCApplication20190814View::CMFCApplication20190814View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication20190814View::~CMFCApplication20190814View()
{
}

BOOL CMFCApplication20190814View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCApplication20190814View 그리기

void CMFCApplication20190814View::OnDraw(CDC* pDC)
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int x, y;
	if (pDoc->InPutImg != NULL) //첫 번째 이미지 파일 처리
	{
		if (pDoc->depth == 1) //흑백 데이터 처리
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InPutImg[y][x], pDoc->InPutImg[y][x], pDoc->InPutImg[y][x]));
		}
		else //컬러 데이터 처리 x*3+0,x*3+1,x*3+2로 rgb 나눠서 처리
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InPutImg[y][3*x+0], pDoc->InPutImg[y][3*x+1], pDoc->InPutImg[y][3*x+2]));
		}
	}
	if (pDoc->ResultImg != NULL) //이미지 파일에 가공해 결과 이미지 출력
	{
		if (pDoc->depth == 1) //흑백 데이터 처리
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20 + x), y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));

		}
		else //컬러 데이터 처리
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20 + x), y, RGB(pDoc->ResultImg[y][3 * x + 0], pDoc->ResultImg[y][3 * x + 1], pDoc->ResultImg[y][3 * x + 2]));
		}
	}
	if (pDoc->InPutImg2 != NULL) //두 영상의 이미지 처리할 때 사용함
	{
		if (pDoc->depth == 1) { // 흑백 데이터 처리
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(2*((pDoc->ImageWidth + 20)) + x, y, RGB(pDoc->InPutImg2[y][x], pDoc->InPutImg2[y][x], pDoc->InPutImg2[y][x]));
		}
		else	//컬러 데이터 처리
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(2*((pDoc->ImageWidth + 20)) + x, y, RGB(pDoc->InPutImg2[y][3 * x + 0], pDoc->InPutImg2[y][3 * x + 1], pDoc->InPutImg2[y][3 * x + 2]));
		}
	}
	if (pDoc->gResultImg != NULL) //이미지 파일에 가공해 결과 이미지 출력
	{
		if (pDoc->depth == 1) //흑백 데이터 처리
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight+20+y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));

		}
		else //컬러 데이터 처리
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImg[y][3 * x + 0], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
		}
	}
}

void CMFCApplication20190814View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMFCApplication20190814View 진단

#ifdef _DEBUG
void CMFCApplication20190814View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplication20190814View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplication20190814Doc* CMFCApplication20190814View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication20190814Doc)));
	return (CMFCApplication20190814Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication20190814View 메시지 처리기



void CMFCApplication20190814View::OnPixeladd()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	if (pDoc->InPutImg == NULL)	return;

	int x, y,value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) 
		{
			if (pDoc->depth == 1) //흑백 이미지 처리 depth가 1일때
			{
				value = pDoc->InPutImg[y][x] + 30; //픽셀 값에 30을 키운 값을 value 변수에 저장
				if (value > 255) value = 255; //픽셀 값의 최대값은 255이므로 255초과가 안되게 저장
				else if (value < 0) value = 0; //마찬가지로 최소값은 0이므로 0미만이면 0으로 저장
				pDoc->ResultImg[y][x] = value; //value 값을 결과 이미지로 전달
			}
			else //컬러 이미지 처리
			{
				value = pDoc->InPutImg[y][3 * x + 0] + 30; //Red 값을 처리함 
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				value = pDoc->ResultImg[y][3 * x + 0];

				value = pDoc->InPutImg[y][3 * x + 1] + 30; // Green 값을 처리함
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				value = pDoc->ResultImg[y][3 * x + 1];

				value = pDoc->InPutImg[y][3 * x + 2] + 30; //Blue 값을 처리함
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
		
	Invalidate(); //화면에 보여주게 함
}


void CMFCApplication20190814View::OnPixelmul()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	if (pDoc->InPutImg == NULL)	return;

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) 
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InPutImg[y][x] *2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = pDoc->InPutImg[y][3 * x + 0] *2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = pDoc->InPutImg[y][3 * x + 1] *2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = pDoc->InPutImg[y][3 * x + 2] *2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnPixelsub()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InPutImg[y][x] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = pDoc->InPutImg[y][3 * x + 0] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = pDoc->InPutImg[y][3 * x + 1] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = pDoc->InPutImg[y][3 * x + 2] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnPixeldiv()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InPutImg[y][x] / 2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = pDoc->InPutImg[y][3 * x + 0] / 2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = pDoc->InPutImg[y][3 * x + 1] / 2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = pDoc->InPutImg[y][3 * x + 2] / 2;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnPixelHistoEq() //히스토그램 평활화
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	int x, y, i, k;
	int acc_hist=0;
	float N = (float)(pDoc->ImageHeight*pDoc->ImageWidth); //전체화소의 수 나중에 나누기 때문에 float로 선언
	int hist[256],sum[256];
	int rhist[256], rsum[256], ghist[256], gsum[256], bhist[256], bsum[256];
	int r_acc_hist = 0, g_acc_hist = 0, b_acc_hist = 0;


	for (i = 0; i < 256; i++) //각 히스토그램을 초기화
	{
		hist[i] = 0;
		rhist[i] = 0; 
		ghist[i] = 0;
		bhist[i] = 0; 
	}
	//히스토그램 구하기
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) 
				hist[pDoc->InPutImg[y][x]]++;  //히스토그램 값을 구함(흑백에서만 사용)
			else
			{
				rhist[pDoc->InPutImg[y][3 * x + 0]]++; //Red 값의 히스토그램을 구함(컬러에서 사용)
				ghist[pDoc->InPutImg[y][3 * x + 1]]++; //Green 값의 히스토그램을 구함(컬러에서 사용)
				bhist[pDoc->InPutImg[y][3 * x + 2]]++; //Blue 값의 히스토그램을 구함(컬러에서 사용)
			}
		}
	//누적분포 구하기
	for (i = 0; i < 256; i++)
	{
		if (pDoc->depth == 1) { //히스토그램의 누적분포 구함
			acc_hist += hist[i];
			sum[i] = acc_hist;
		}
		else //RGB색에 따른 누적분포를 구함
		{
			r_acc_hist += rhist[i];
			rsum[i] = r_acc_hist;
			g_acc_hist += ghist[i];
			gsum[i] = g_acc_hist;
			b_acc_hist += bhist[i];
			bsum[i] = b_acc_hist;
		}
	}

	//평활화 화소값저장
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x <pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				k = pDoc->InPutImg[y][x];
				pDoc->ResultImg[y][x] = sum[k]/ N * 255; //히스토그램 평활화 공식 =sum[InputImg[y][x]] /전체 화소 수(N) *255
				//n이나 sum[k]를 float형으로 바꾸지 않으면 소수점이 날아가서 0으로 되어 검은화면으로 나옴
			}
			else //컬러 값을 RGB따로 결과 보여줌
			{
				k = pDoc->InPutImg[y][3*x+0];
				pDoc->ResultImg[y][3 * x + 0] = rsum[k] / N * 255;
				k = pDoc->InPutImg[y][3*x+1];
				pDoc->ResultImg[y][3 * x + 1] = gsum[k] / N * 255;
				k = pDoc->InPutImg[y][3*x+2];
				pDoc->ResultImg[y][3 * x + 2] = bsum[k] / N * 255;
			}
		}

	Invalidate();
}


void CMFCApplication20190814View::OnPixelContrastStretching() //명암대비 스트레칭
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	int x, y, i, k;
	int min = 256;
	int max = -1;
	int rmin = 256, rmax = -1, gmin = 256, gmax = -1, bmin = 256, bmax = -1;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) { //명암대비 스트레칭 최대값과 최솟값을 구하기 위해 사용(흑백) 
				if (min > pDoc->InPutImg[y][x])
					min = pDoc->InPutImg[y][x];
				if (max < pDoc->InPutImg[y][x])
					max = pDoc->InPutImg[y][x];
			}
			else //컬러 이미지
			{
				if (min > pDoc->InPutImg[y][x])
					min = pDoc->InPutImg[y][x];
				if (max < pDoc->InPutImg[y][x])
					max = pDoc->InPutImg[y][x];

				if (rmin > pDoc->InPutImg[y][3*x+0])
					rmin = pDoc->InPutImg[y][3*x+0];
				if (rmax < pDoc->InPutImg[y][3*x+0])
					rmax = pDoc->InPutImg[y][3*x+0];

				if (gmin > pDoc->InPutImg[y][3 * x + 1])
					gmin = pDoc->InPutImg[y][3 * x + 1];
				if (gmax < pDoc->InPutImg[y][3 * x + 1])
					gmax = pDoc->InPutImg[y][3 * x + 1];

				if (bmin > pDoc->InPutImg[y][3 * x + 2])
					bmin = pDoc->InPutImg[y][3 * x + 2];
				if (bmax < pDoc->InPutImg[y][3 * x + 2])
					bmax = pDoc->InPutImg[y][3 * x + 2];
			}
	}
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				k = pDoc->InPutImg[y][x];
				pDoc->ResultImg[y][x] = ((k - min) * 255) / (float)(max - min); 
				// 명암대비 스트레칭 공식 = (InPutImg[y][x]-min)/(max-min) *255여기서 나눌떄 float으로 형변환을 안해주면 오류 발생
			}
			else //RGB에 최대 최소 값을 구해서 3개로 출력해야함
			{
				k = pDoc->InPutImg[y][3 * x + 0];
				pDoc->ResultImg[y][3 * x + 0] = ((k - rmin) * 255) / (float)(rmax - rmin);
				k = pDoc->InPutImg[y][3 * x + 1];
				pDoc->ResultImg[y][3 * x + 1] = ((k - gmin) * 255) / (float)(gmax - gmin);
				k = pDoc->InPutImg[y][3 * x + 2];
				pDoc->ResultImg[y][3 * x + 2] = ((k - bmin) * 255) / (float)(bmax - bmin);
			}
		}
	Invalidate();  
}


void CMFCApplication20190814View::OnPixelBinarization() //이진화
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	int x, y, value;
	int threshold = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				if (pDoc->InPutImg[y][x] > threshold) pDoc->ResultImg[y][x] = 255;
				else
					pDoc->ResultImg[y][x] = 0;
			}
			else 
			{
				if (pDoc->InPutImg[y][3 * x + 0] + pDoc->InPutImg[y][3 * x + 1] + pDoc->InPutImg[y][3 * x + 2] > threshold) { 
					//컬러영상의 이진화를 할때 RGB값을 모두 더한 것을 기준값과 비교
					pDoc->ResultImg[y][3 * x + 0] = 255;
					pDoc->ResultImg[y][3 * x + 1] = 255;
					pDoc->ResultImg[y][3 * x + 2] = 255;
				}
				else {
					pDoc->ResultImg[y][3 * x + 0] = 0;
					pDoc->ResultImg[y][3 * x + 1] = 0;
					pDoc->ResultImg[y][3 * x + 2] = 0;
				}
			}
			
		}

	Invalidate();

}


void CMFCApplication20190814View::OnPixelTwoImageAdd() //이미지 2개의 합
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK)
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	//LoadTwoImage();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{	
			if (pDoc->depth == 1) {
				value = 0.5*pDoc->InPutImg[y][x] + 0.5*pDoc->InPutImg2[y][x]; //두 영상의 합을 할때 서로 영상의 퍼센트를 곱하여 표시
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = 0.5*pDoc->InPutImg[y][3*x+0] + 0.5*pDoc->InPutImg2[y][3*x+0];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;
				value = 0.5*pDoc->InPutImg[y][3 * x + 1] + 0.5*pDoc->InPutImg2[y][3 * x + 1];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;
				value = 0.5*pDoc->InPutImg[y][3 * x + 2] + 0.5*pDoc->InPutImg2[y][3 * x + 2];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();

}
/*void CMFCApplication20190814View::LoadTwoImage() //두 개의 이미지를 받음
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(pDoc->InPutImg2, 256 * 256);
		file.Close();
	}
}
//ppm,pgm,raw받는 부분으로 수정 해야함
*/
void CMFCApplication20190814View::OnPixelTwoImageSub() //이미지 2개의 값의 뺼셈
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK)
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	//LoadTwoImage()

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{	
			if (pDoc->depth == 1) {
				value = abs(0.5*pDoc->InPutImg[y][x] - 0.5*pDoc->InPutImg2[y][x]);
				if (value > 64) value = 255;
				else			value = 0;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = abs(0.5*pDoc->InPutImg[y][3*x+0] - 0.5*pDoc->InPutImg2[y][3 * x + 0]);
				if (value > 64) value = 255;
				else			value = 0;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = abs(0.5*pDoc->InPutImg[y][3 * x + 1] - 0.5*pDoc->InPutImg2[y][3 * x + 1]);
				if (value > 64) value = 255;
				else			value = 0;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = abs(0.5*pDoc->InPutImg[y][3 * x + 2] - 0.5*pDoc->InPutImg2[y][3 * x + 2]);
				if (value > 64) value = 255;
				else			value = 0;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnRegionSmoothing() //흐리게 보이게 하는 마스크
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	float kernel[3][3] = { {1 / 9.0,1 / 9.0,1 / 9.0},	//결국 1px을 출력하는 것이기 때문에 총 합이 1이어야함
						   {1 / 9.0,1 / 9.0,1 / 9.0},
						   {1 / 9.0,1 / 9.0,1 / 9.0} };
	Convolve(pDoc->InPutImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CMFCApplication20190814View::Convolve(unsigned char ** InImg, unsigned char ** OutImg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y, value,i,j;
	float sum,redsum,greensum,bluesum;

	for (y = 1; y < rows-1; y++)				//가로 세로 값-1로 반복 why? 3*3으로 주변 값을 참조하여 사용하는데 태두리에 있는 값들은 주변 값 9개를 참조하지 못하기 때문에 제외
		for (x = 1; x < cols-1; x++)
		{
			if (depth == 1) {
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += InImg[y - 1 + j][x - 1 + i] * mask[j][i]; //마스크 값은 위에 호출할 때 사용함 InPutImg * mask 값으로 영상처리
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				OutImg[y][x] = sum;	//출력하는 값은 InPutImg*mask 값의 총 합
			}
			else
			{
				redsum = 0; greensum = 0; bluesum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++) //역시 컬러 처리는 RGB따로 따로 처리
					{
						redsum += InImg[y - 1 + j][3*(x - 1 + i)+0] * mask[j][i];
						greensum += InImg[y - 1 + j][3 * (x - 1 + i) + 1] * mask[j][i];
						bluesum += InImg[y - 1 + j][3 * (x - 1 + i) + 2] * mask[j][i];
					}
				redsum += bias;
				greensum += bias;
				bluesum += bias;

				if (redsum > 255) redsum = 255;
				else if (redsum < 0) redsum = 0;
				if (greensum > 255) greensum = 255;
				else if (greensum < 0) greensum = 0;
				if (bluesum > 255) bluesum = 255;
				else if (bluesum < 0) bluesum = 0;

				OutImg[y][3 * x + 0] = redsum;
				OutImg[y][3 * x + 1] = greensum;
				OutImg[y][3 * x + 2] = bluesum;
			}
		}
}

void CMFCApplication20190814View::OnRegionSharpening() //선명하게 보이는 마스크
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	float kernel[3][3] = { {0,	-1,	0},
						   {-1,	5,	-1},
						   {0,	-1,	0} };
	Convolve(pDoc->InPutImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CMFCApplication20190814View::OnRegionEmbossing() //엠보싱 효과 마스크
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	float kernel[3][3] = { {-1,	0,	0},
						   {0,	0,	0},
						   {0,	0,	1} };
	Convolve(pDoc->InPutImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}



void CMFCApplication20190814View::OnRegionPrewitt()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,	-1,	-1}, //수평방향이 더 잘나오게 함
						   {0,	0,	0},
						   {1,	1,	1} };
	float Vmask[3][3] = { { -1,	0,	1},  //수직방향이 더 잘나오게 함
						   {-1,	0,	1},
						   {-1,	0,	1} };
	unsigned char **Er, **Ec;
	int x, y,value;
	//메모리 할당
	Er = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	Ec = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
	}

	Convolve(pDoc->InPutImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InPutImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);
	
	for(y=0;y<pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++) //RGB에 동일한 연산을 해주어서 컬러처리 가능
		{	
			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = sqrt(Er[y][3*x+0] * Er[y][3*x+0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
		//메모리 해제(메모리를 할당해줬으니 해제도 해주어야함)
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}



void CMFCApplication20190814View::OnRegionRoberts()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,	0,	0},
						   {0,	1,	0},
						   {0,	0,	0} };
	float Vmask[3][3] = { {0,	0,	-1}, 
						   {0,	1,	0},
						   {0,	0,	0} };
	unsigned char **Er, **Ec;
	int x, y, value;
	//메모리 할당
	Er = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	Ec = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
	}

	Convolve(pDoc->InPutImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InPutImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) //RGB에 동일한 연산을 해주어서 컬러처리 가능
		{
			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	//메모리 해제(메모리를 할당해줬으니 해제도 해주어야함)
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CMFCApplication20190814View::OnRegionSobel()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,	-2,	-1}, //수평방향이 더 잘나오게 함
						   {0,	0,	0},
						   {1,	2,	1} };
	float Vmask[3][3] = { { -1,	0,	1},  //수직방향이 더 잘나오게 함
						   {-2,	0,	2},
						   {-1,	0,	1} };
	unsigned char **Er, **Ec;
	int x, y, value;
	//메모리 할당
	Er = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	Ec = (unsigned char **)malloc(pDoc->ImageHeight * sizeof(unsigned char *));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth*pDoc->depth);
	}

	Convolve(pDoc->InPutImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InPutImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) //RGB에 동일한 연산을 해주어서 컬러처리 가능
		{
			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}
	//메모리 해제(메모리를 할당해줬으니 해제도 해주어야함)
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}




void CMFCApplication20190814View::OnRegionAverageFiltering() //평균 마스크 흐릿하게 보인다. 가우시안 잡음 제거에 좋음
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y,j,i;
	int xcor, ycor;
	int sum,count;
	int rsum, bsum, gsum;

	for (y = 0; y < pDoc->ImageHeight; y++) //평균내는 영역
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				count = 0;
				for (j = -2; j <= 2; j++) //이 곳의 영역을 줄이면 덜 흐릿하게 보임(주변에서 가져오는 픽셀의 수)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;

						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							sum += pDoc->InPutImg[ycor][xcor];
							count++;
						}
					}
				pDoc->ResultImg[y][x] = sum / count;
			}
			else
			{
				rsum = bsum=gsum=0;
				count = 0;
				for (j = -2; j <= 2; j++) //이 곳의 영역을 줄이면 덜 흐릿하게 보임(주변에서 가져오는 픽셀의 수)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;

						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							rsum += pDoc->InPutImg[ycor][3 * xcor + 0];
							gsum += pDoc->InPutImg[ycor][3 * xcor + 1];
							bsum += pDoc->InPutImg[ycor][3 * xcor + 2];
							count++;
						}
					}
				pDoc->ResultImg[y][3 * x + 0] = rsum / count;
				pDoc->ResultImg[y][3 * x + 1] = gsum / count;
				pDoc->ResultImg[y][3 * x + 2] = bsum / count;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnRegionMedianFiltering() //임펄스 잡음처리 가우시안 잡음도 제거 하지만 깔끔?남는게 있음 
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y, j, i;
	int n[9];
	int temp;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)	//3*3median필터
		{	
			if (pDoc->depth == 1)
			{
				n[0] = pDoc->InPutImg[y - 1][x - 1];
				n[1] = pDoc->InPutImg[y - 1][x - 0];
				n[2] = pDoc->InPutImg[y - 1][x + 1];
				n[3] = pDoc->InPutImg[y - 0][x - 1];
				n[4] = pDoc->InPutImg[y - 0][x - 0];
				n[5] = pDoc->InPutImg[y - 0][x + 1];
				n[6] = pDoc->InPutImg[y + 1][x - 1];
				n[7] = pDoc->InPutImg[y + 1][x - 0];
				n[8] = pDoc->InPutImg[y + 1][x + 1];

				//sorting(정렬)
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->ResultImg[y][x] = n[4]; //가운데이 있는값 n[4]를 ResultImg에 저장
			}
			else //컬러
			{
				n[0] = pDoc->InPutImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InPutImg[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InPutImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InPutImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InPutImg[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InPutImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InPutImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InPutImg[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InPutImg[y + 1][3 * (x + 1) + 0];

				//sorting(정렬)
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->ResultImg[y][3*x+0] = n[4]; //가운데이 있는값 n[4]를 R값에 저장

				n[0] = pDoc->InPutImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InPutImg[y - 1][3 * (x - 0) + 1];
				n[2] = pDoc->InPutImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InPutImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InPutImg[y - 0][3 * (x - 0) + 1];
				n[5] = pDoc->InPutImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InPutImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InPutImg[y + 1][3 * (x - 0) + 1];
				n[8] = pDoc->InPutImg[y + 1][3 * (x + 1) + 1];

				//sorting(정렬)
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->ResultImg[y][3 * x + 1] = n[4]; //가운데이 있는값 n[4]를 G값에 저장

				n[0] = pDoc->InPutImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InPutImg[y - 1][3 * (x - 0) + 2];
				n[2] = pDoc->InPutImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InPutImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InPutImg[y - 0][3 * (x - 0) + 2];
				n[5] = pDoc->InPutImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InPutImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InPutImg[y + 1][3 * (x - 0) + 2];
				n[8] = pDoc->InPutImg[y + 1][3 * (x + 1) + 2];

				//sorting(정렬)
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->ResultImg[y][3 * x + 2] = n[4]; //가운데이 있는값 n[4]를 B값에 저장
			}

		}
	Invalidate();
}


void CMFCApplication20190814View::OnMopologyColorGray() //형태학적변환에 필요함 WHY? 흑백에 관한데이터를 처리 해야함
{ //칼라를 다시 쓰려면 다시 불러와야 한다
	CMFCApplication20190814Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InPutImg[y][3 * x + 0] + pDoc->InPutImg[y][3 * x + 1] + pDoc->InPutImg[y][3 * x + 2]) / 3;
			
			pDoc->InPutImg[y][3 * x + 0] = gray;
			pDoc->InPutImg[y][3 * x + 1] = gray;
			pDoc->InPutImg[y][3 * x + 2] = gray;
			
		}
	Invalidate();
}


void CMFCApplication20190814View::OnMopologyBinarization()//형태학적처리를 사용하기 위해서 이진화를 함
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y;
	int thresh=128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InPutImg[y][x] > thresh)
					pDoc->InPutImg[y][x] = 255;
				else
					pDoc->InPutImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->InPutImg[y][3 * x + 0] + pDoc->InPutImg[y][3 * x + 1] + pDoc->InPutImg[y][3 * x + 2]) / 3 > thresh)
				{
					pDoc->InPutImg[y][3 * x + 0] = 255;
					pDoc->InPutImg[y][3 * x + 1] = 255;
					pDoc->InPutImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InPutImg[y][3 * x + 0] = 0;
					pDoc->InPutImg[y][3 * x + 1] = 0;
					pDoc->InPutImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnMopologyErosion() //침식연산 검정색 부분이 늘어남
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	//최솟값 필터
	int x, y, j, i;
	int min,rmin,gmin,bmin=255;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InPutImg[y + j][x + i] < min)
							min = pDoc->InPutImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = min;
			}
			else
			{
				rmin = 255; gmin = 255; bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++) 
					{
						if (pDoc->InPutImg[y + j][3 *(x + i) + 0] < rmin)
							rmin = pDoc->InPutImg[y + j][3 * (x + i) + 0];
						if (pDoc->InPutImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InPutImg[y + j][3 * (x + i) + 1];
						if (pDoc->InPutImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InPutImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmin;
				pDoc->ResultImg[y][3 * x + 1] = gmin;
				pDoc->ResultImg[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnMopologyDilation() //팽창연산 흰색 부분이 늘어남
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	//최대값 필터
	int x, y, j, i;
	int max, rmax, gmax, bmax = 0;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InPutImg[y + j][x + i] > max)
							max = pDoc->InPutImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = max;
			}
			else
			{
				rmax = 0; gmax = 0; bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InPutImg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InPutImg[y + j][3 * (x + i) + 0];
						if (pDoc->InPutImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InPutImg[y + j][3 * (x + i) + 1];
						if (pDoc->InPutImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InPutImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmax;
				pDoc->ResultImg[y][3 * x + 1] = gmax;
				pDoc->ResultImg[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
}



void CMFCApplication20190814View::OnMopologyOpening() //열림 연산 침식반복 후 팽창반복
{
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	//위 내용 침식연산 3번

	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	//위 내용 팽창연산 3번
}


void CMFCApplication20190814View::CopyResultToinput() 
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->InPutImg[y][x] = pDoc->ResultImg[y][x];
		}

}


void CMFCApplication20190814View::OnMopologyClosing() //닫힘연산 팽창반복 후 침식반복
{
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	OnMopologyDilation();
	CopyResultToinput();
	//위 내용 팽창연산 3번

	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	CopyResultToinput();
	OnMopologyErosion();
	//위 내용 침식연산 3번
}



void CMFCApplication20190814View::OnGeometryZoominPixelCopy()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3; //x를 증가시키는 비율을 적음
	int yscale = 2;
	
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth*xscale;
	pDoc->gImageHeight = pDoc->ImageHeight*yscale;
	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth*pDoc->depth);
	}
		//역방향사상
		for (y = 0; y < pDoc->gImageHeight; y++)
			for (x = 0; x < pDoc->gImageWidth; x++)
			{
				if(pDoc->depth==1)
				pDoc->gResultImg[y][x] = pDoc->InPutImg[y / yscale][x / xscale];
				else
				{
					pDoc->gResultImg[y][3 * x + 0] = pDoc->InPutImg[y / yscale][3 * (x / xscale) + 0];
					pDoc->gResultImg[y][3 * x + 1] = pDoc->InPutImg[y / yscale][3 * (x / xscale) + 1];
					pDoc->gResultImg[y][3 * x + 2] = pDoc->InPutImg[y / yscale][3 * (x / xscale) + 2];
				}
			}
/*
	전방향사상		전방향 사상은 구멍이 생겨 역방향 사상이 더 좋다.
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultImg[y*yscale][x*xscale] = pDoc->InPutImg[y][x];
		}
	*/
	Invalidate();
}


void CMFCApplication20190814View::OnGeometryZoominBilinearInterpolation() //양선형 보간법
//역방향사상에 비해 계단현상이 훨씬 줄어듬
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y;

	float xscale = 2.3; //x를 증가시키는 비율을 적음
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth*xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight*yscale + 0.5;
	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth*pDoc->depth);
	}
	//양선형 보간법 좌표 4개의 값을 구하고 구하고자하는 x좌표가 있는E와F를 구하고 E,F로 Y값을 구함
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			//소수점만 남김
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;
			//각 좌표 값을 구함
			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				//위 줄의 x값인 E값과 아래 줄의 x값인 F값을 구함
				E = (1 - alpha)*pDoc->InPutImg[Ay][Ax] + alpha * pDoc->InPutImg[By][Bx];
				F = (1 - alpha)*pDoc->InPutImg[Cy][Cx] + alpha * pDoc->InPutImg[Dy][Dx];
				//E와F를 사용하여 y값을 구함
				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else 
			{ 
				//컬러 처리
				E = (1 - alpha)*pDoc->InPutImg[Ay][3 * Ax + 0] + alpha * pDoc->InPutImg[By][3 * Bx + 0];
				F = (1 - alpha)*pDoc->InPutImg[Cy][3 * Cx + 0] + alpha * pDoc->InPutImg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;
				E = (1 - alpha)*pDoc->InPutImg[Ay][3 * Ax + 1] + alpha * pDoc->InPutImg[By][3 * Bx + 1];
				F = (1 - alpha)*pDoc->InPutImg[Cy][3 * Cx + 1] + alpha * pDoc->InPutImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;
				E = (1 - alpha)*pDoc->InPutImg[Ay][3 * Ax + 2] + alpha * pDoc->InPutImg[By][3 * Bx + 2];
				F = (1 - alpha)*pDoc->InPutImg[Cy][3 * Cx + 2] + alpha * pDoc->InPutImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnGeometryZoomoutSubsampling()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int xscale = 3;			// 1/3
	int yscale = 2;			// 1/2
	int x, y;

	if (pDoc->gResultImg != NULL) //기존에 할당되어있는 메모리 삭제
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}
	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc((pDoc->gImageWidth)*(pDoc->depth));
	}
	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->InPutImg[y*yscale][x*xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InPutImg[y*yscale][3 * (x*xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InPutImg[y*yscale][3 * (x*xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InPutImg[y*yscale][3 * (x*xscale) + 2];
			}
		}
	Invalidate();
}



void CMFCApplication20190814View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();
	OnGeometryZoomoutSubsampling();
	CopyResultToinput();
}


void CMFCApplication20190814View::OnGeometryAvgFiltering()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();

	int xscale = 3;			// 1/3
	int yscale = 2;			// 1/2
	int x, y,j,i;
	int sum;
	int src_x, src_y;
	int rsum, gsum, bsum;

	if (pDoc->gResultImg != NULL) //기존에 할당되어있는 메모리 삭제
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}
	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc((pDoc->gImageWidth)*(pDoc->depth));
	}
	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y+=yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale)
		{
			sum = 0;
			rsum = 0;
			gsum = 0;
			bsum = 0;
			if (pDoc->depth == 1)
			{
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->InPutImg[src_y][src_x];
					}
				pDoc->gResultImg[y/yscale][x/xscale] = sum / (yscale*xscale);
			}
			else
			{
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->InPutImg[src_y][3 * src_x + 0];
						gsum += pDoc->InPutImg[src_y][3 * src_x + 1];
						bsum += pDoc->InPutImg[src_y][3 * src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		
	}
	Invalidate();
}



#define PI 3.1416926521
#include "CAngleDialog.h"
void CMFCApplication20190814View::OnGeometryRotation()
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30; //degree(적은수만큼 회전)
	float radian;
	int Hy;
	int Cx, Cy;
	int xdiff, ydiff;
	int x, y;
	int x_sourse, y_sourse;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)		return;
	angle = dlg.m_iAngle;


	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL) //기존에 할당되어있는 메모리 삭제
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}
	pDoc->gImageWidth = (int)(pDoc->ImageHeight* fabs(cos(PI / 2 - radian)) + pDoc->ImageWidth*fabs(cos(radian)));
	pDoc->gImageHeight = (int)(pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian)));
	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc((pDoc->gImageWidth)*(pDoc->depth));
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y=-ydiff; y<pDoc->gImageHeight-ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_sourse = (int)((Hy - y - Cy)*sin(radian) + (x - Cx)*cos(radian) + Cx);
			y_sourse = (int)(Hy - ((Hy - y - Cy)*cos(radian) - (x - Cx)*sin(radian) + Cy));

			if (pDoc->depth == 1)
			{
				if (x_sourse < 0 || x_sourse > (pDoc->ImageWidth) - 1 || y_sourse < 0 || y_sourse > (pDoc->ImageHeight) - 1)
				pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InPutImg[y_sourse][x_sourse];
			}
			else
			{
				if (x_sourse < 0 || x_sourse > (pDoc->ImageWidth) - 1 || y_sourse < 0 || y_sourse > (pDoc->ImageHeight) - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InPutImg[y_sourse][3 * (x_sourse)+0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InPutImg[y_sourse][3 * (x_sourse)+1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InPutImg[y_sourse][3 * (x_sourse)+2];
				}
			}
		}
	Invalidate();
}


void CMFCApplication20190814View::OnGeometryHolizantialFup() //좌우대칭
{
	CMFCApplication20190814Doc* pDoc = GetDocument();
	
	int x, y;

	for(y=0;y<pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if(pDoc->depth==1)
			pDoc->ResultImg[y][x] = pDoc->InPutImg[y][(pDoc->ImageWidth) - 1 - x];
			else
			{
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InPutImg[y][3 * ((pDoc->ImageWidth) - 1 - x) + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InPutImg[y][3 * ((pDoc->ImageWidth) - 1 - x) + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InPutImg[y][3 * ((pDoc->ImageWidth) - 1 - x) + 2];
			}
		}
	Invalidate();
}



void CMFCApplication20190814View::OnGeometryVerticalFup() //상하대칭
{

	CMFCApplication20190814Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if(pDoc->depth==1)
			pDoc->ResultImg[y][x] = pDoc->InPutImg[(pDoc->ImageHeight) - 1 - y][x];
			else
			{
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InPutImg[(pDoc->ImageHeight) - 1 - y][3 * x + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InPutImg[(pDoc->ImageHeight) - 1 - y][3 * x + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InPutImg[(pDoc->ImageHeight) - 1 - y][3 * x + 2];
			}
		}
	Invalidate();
}
//p가 i q가 i+1
//워핑 한장의 영상을 우리가 원하는 방향으로 움직임
//11주차
