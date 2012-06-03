using Dalssoft.DiagramNet;
using System.Drawing;
using System;

namespace Dalssoft.DiagramNet
{
    [Serializable]
    public class AdvancedStraightLinkElement : StraightLinkElement
    {
        private BaseElement StartElement;
        private BaseElement EndElement;

        public AdvancedStraightLinkElement(BaseElement StartElement, ConnectorElement conn1, BaseElement EndElement, ConnectorElement conn2)
            : base(conn1, conn2)
		{
			this.StartElement = StartElement;
            this.EndElement = EndElement;
		}

        internal override void Draw(System.Drawing.Graphics g)
        {
            Rectangle r1 = Rectangle.Empty;
            Rectangle r2 = Rectangle.Empty;

            if (this.StartElement.invalidateRec == Rectangle.Empty)
                r1 = this.StartElement.GetRectangle();
            else
                r1 = this.StartElement.invalidateRec;

            if (this.EndElement.invalidateRec == Rectangle.Empty)
                r2 = this.EndElement.GetRectangle();
            else
                r2 = this.EndElement.invalidateRec;

            Point p1 = IntersectionPoint(r1);
            Point p2 = IntersectionPoint(r2);

            IsInvalidated = false;

            if ((p1 != Point.Empty) && (p2 != Point.Empty))
            {
                //Fill rectangle
                Color borderColor1;
                if (line1.Opacity == 100)
                    borderColor1 = line1.BorderColor;
                else
                    borderColor1 = Color.FromArgb((int)(255.0f * (line1.Opacity / 100.0f)), line1.BorderColor);

                Pen p;
                p = new Pen(borderColor1, line1.BorderWidth);

                p.StartCap = line1.StartCap;
                p.EndCap = line1.EndCap;                
                g.DrawLine(p, p1, p2);

                p.Dispose();
            }
            else
            {
                base.Draw(g);
            }

        }

        private Point IntersectionPoint(Rectangle rect)
        {
            Point result = Point.Empty;
            Point LeftUp = new Point(rect.X-5, rect.Y-5);
            Point LeftDown = new Point(rect.X-5, rect.Y + rect.Height+10);

            Point RightUp = new Point(rect.X+5 + rect.Width, rect.Y-5);
            Point RightDown = new Point(rect.X + rect.Width+10, rect.Y + rect.Height+10);

            Diagram.NET.element.MathHelper.pt point;

            //Верхний
            Diagram.NET.element.MathHelper.segment s1 = new Diagram.NET.element.MathHelper.segment(LeftUp, RightUp);
            Diagram.NET.element.MathHelper.segment s2 = new Diagram.NET.element.MathHelper.segment(this.line1.Point1, this.line1.Point2);
            point = Diagram.NET.element.MathHelper.segments_intersection(s1,s2);
            if (point != null) return new Point((int)point.x, (int)point.y);
            

            //Правый
            s1 = new Diagram.NET.element.MathHelper.segment(RightUp, RightDown);
            point = Diagram.NET.element.MathHelper.segments_intersection(s1, s2);
            if (point != null) return new Point((int)point.x, (int)point.y);
            
            //Нижний
            s1 = new Diagram.NET.element.MathHelper.segment(RightDown, LeftDown);
            point = Diagram.NET.element.MathHelper.segments_intersection(s1, s2);
            if (point != null) return new Point((int)point.x, (int)point.y);
            
            //Левый
            s1 = new Diagram.NET.element.MathHelper.segment(LeftDown, LeftUp);
            point = Diagram.NET.element.MathHelper.segments_intersection(s1, s2);
            if (point != null) return new Point((int)point.x, (int)point.y);
            

            return result;
        }
    }
}
