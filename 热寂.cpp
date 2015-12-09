//因为还不太会怎么改设置，所以先上转个cpp应付，可以明确这语言不是c++，是种类c语言
#property copyright "阿斯伯格"
#property link      "阿斯伯格"
extern datetime 挂单本地电脑时间;
extern int 挂单价距离当时现价点数 = 100;
extern int 挂单有效分钟数 = 10;
extern double 挂单下单量;
extern int 挂单止损点数 = 70;
extern int 挂单止盈点数;
extern int 挂单成交后移动止损点数;
extern int magic = 405215;
datetime dangshi = 0;
int sells = 0;
int buys = 0;
int end = 0;


int kaidanok = 0;
int kaiguan = 0;
int ticket = 0;

int init()
{
	DrawLabel("will1", "sell is better", 2, 13, "宋体", 9, Aqua, 0);
	dangshi = TimeLocal();
	return(0);
}
int deinit()
{
	return(0);
}
int start()
{


	if (挂单本地电脑时间<dangshi)
		if (end == 0)
		{
			Alert("这个挂单时间已经过了还怎么挂单");
			end = 1;
		}






	if (挂单本地电脑时间 <= TimeLocal())
		if (end != 1)
		{
			sells = OrderSend(Symbol(), OP_SELLSTOP, 挂单下单量, Bid - 挂单价距离当时现价点数*Point, 70, Ask + 挂单止损点数*Point, 0, 0, magic, TimeLocal() + 挂单有效分钟数 * 60, White);
			buys = OrderSend(Symbol(), OP_BUYSTOP, 挂单下单量, Ask + 挂单价距离当时现价点数*Point, 70, Ask - 挂单止损点数*Point, 0, 0, magic, TimeLocal() + 挂单有效分钟数 * 60, White);
		}


	for (int i = 0; i<OrdersTotal(); i++)
	{
		if (OrderSelect(i, SELECT_BY_POS, MODE_TRADES) == TRUE)
			end = 1;
	}

	if (sells == -1 && buys == -1)
		end = 0;

	Comment("sells=", sells, "buys=", buys, "end=", end);
	return(0);
}
/*
void yidong()
{
for(int i=0;i<OrdersTotal();i++)//移动止损通用代码,次代码会自动检测buy和sell单并对其移动止损
{
if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES)==true)
{
if(OrderType()==0 && OrderSymbol()==Symbol() && OrderMagicNumber()==magic)
{
if((Bid-OrderOpenPrice()) >=Point*挂单成交后移动止损点数)
{
if(OrderStopLoss()<(Bid-Point*挂单成交后移动止损点数) || (OrderStopLoss()==0))
{
OrderModify(OrderTicket(),OrderOpenPrice(),Bid-Point*挂单成交后移动止损点数,0,0,Green);
}
}
}
if(OrderType()==1 && OrderSymbol()==Symbol() && OrderMagicNumber()==magic)
{
if((OrderOpenPrice()-Ask)>=(Point*挂单成交后移动止损点数))
{
if((OrderStopLoss()>(Ask+Point*挂单成交后移动止损点数)) || (OrderStopLoss()==0))
{
OrderModify(OrderTicket(),OrderOpenPrice(),Ask+Point*挂单成交后移动止损点数,0,0,Red);
}
}
}
}
}
}
*/
void DrawLabel(string name, string text, int X, int Y, string FontName, int FontSize, color FontColor, int zhongxin)
{
	if (ObjectFind(name) != 0)
	{
		ObjectDelete(name);
		ObjectCreate(name, OBJ_LABEL, 0, 0, 0);
		ObjectSet(name, OBJPROP_CORNER, zhongxin);
		ObjectSet(name, OBJPROP_XDISTANCE, X);
		ObjectSet(name, OBJPROP_YDISTANCE, Y);
	}
	// ObjectSetText(name,text,FontSize,FontName,FontColor);
	WindowRedraw();
}
