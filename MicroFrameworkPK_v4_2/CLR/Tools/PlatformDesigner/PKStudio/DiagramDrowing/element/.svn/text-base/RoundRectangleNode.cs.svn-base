using System.Drawing;
using System.Drawing.Drawing2D;
using System;

namespace Dalssoft.DiagramNet
{
    [Serializable]
    public class RoundRectangleNode : RectangleNode
    {

        public RoundRectangleNode()
            : base(0, 0, 100, 100)
        { Radius = 10; }

        public RoundRectangleNode(Rectangle rec)
            : base(rec.Location, rec.Size)
        { Radius = 10; }

        public RoundRectangleNode(Point l, Size s)
            : base(l.X, l.Y, s.Width, s.Height)
        { Radius = 10; }

        public RoundRectangleNode(int top, int left, int width, int height)
            : base(top, left, width, height)
		{
			rectangle = new RectangleElement(top, left, width, height);
			SyncContructors();
            Radius = 10;
		}

        public float Radius { get; set; }        

        protected virtual Brush GetBrush(Rectangle r)
        {
            //Fill rectangle
            Color fill1;
            Color fill2;
            Brush b;
            if (opacity == 100)
            {
                fill1 = FillColor1;
                fill2 = FillColor2;
            }
            else
            {
                fill1 = Color.FromArgb((int)(255.0f * (opacity / 100.0f)), FillColor1);
                fill2 = Color.FromArgb((int)(255.0f * (opacity / 100.0f)), FillColor2);
            }

            if (FillColor2 == Color.Empty)
                b = new SolidBrush(fill1);
            else
            {
                Rectangle rb = new Rectangle(r.X, r.Y, r.Width + 1, r.Height + 1);
                b = new LinearGradientBrush(
                    rb,
                    fill1,
                    fill2,
                    LinearGradientMode.Horizontal);
            }

            return b;
        }

        internal override void Draw(Graphics g)
        {
            IsInvalidated = false;

            Rectangle r = GetUnsignedRectangle();

            //Shadow
            GraphicsPath gp = CreatePath(r.X + 5, r.Y + 5, r.Width, r.Height, Radius);
            //g.FillPath(new SolidBrush(Color.FromArgb((int)(255.0f * (50 / 100.0f)), Color.LightGray)), gp);

            g.FillPath(new SolidBrush(Color.LightGray), gp);

            gp.Dispose();

            //Border
            gp = CreatePath(r.X, r.Y, r.Width, r.Height, Radius);

            Pen p = new Pen(borderColor, borderWidth);
            g.DrawPath(p, gp);            
            p.Dispose();

            //Color
            Brush b = this.GetBrush(r);
            g.FillPath(b, gp);
            gp.Dispose();

            b.Dispose();
        }

        public GraphicsPath CreatePath(float x, float y, float width, float height, float radius)
        {
            GraphicsPath gp = new GraphicsPath();
   
            gp.AddLine(x + radius, y, x + width - (radius * 2), y); // Line
            gp.AddArc(x + width - (radius * 2), y, radius * 2, radius * 2, 270, 90); // Corner
            gp.AddLine(x + width, y + radius, x + width, y + height - (radius * 2)); // Line
            gp.AddArc(x + width - (radius * 2), y + height - (radius * 2), radius * 2, radius * 2, 0, 90); // Corner
            gp.AddLine(x + width - (radius * 2), y + height, x + radius, y + height); // Line
            gp.AddArc(x, y + height - (radius * 2), radius * 2, radius * 2, 90, 90); // Corner
            gp.AddLine(x, y + height - (radius * 2), x, y + radius); // Line
            gp.AddArc(x, y, radius * 2, radius * 2, 180, 90); // Corner
            gp.CloseFigure();

            return gp;
        }
    }
}
