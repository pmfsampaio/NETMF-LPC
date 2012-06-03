using System;
using System.Drawing;

namespace Diagram.NET.element
{
    public class MathHelper
    {
        public class segment {
            public float x1 { get; set; }
            public float y1 { get; set; }
            public float x2 { get; set; }
            public float y2 { get; set; }

            public segment()
            {
            }

            public segment(Point p1, Point p2)
            {
                x1 = p1.X;
                y1 = p1.Y;
                x2 = p2.X;
                y2 = p2.Y;
            }
        };

        public class line
        {
            public float a { get; set; }
            public float b { get; set; }
            public float c { get; set; }

            public bool Compare(line l)
            {
                if (this.a != l.a) return false;
                if (this.b != l.b) return false;
                if (this.c != l.c) return false;
                return true;
            }
        };

        public class pt
        {
            public float x { get; set; }
            public float y { get; set; }
        };


        const double EPS = 1e-6;

        public static bool eq (double a, double b)
        {
	        return Math.Abs(a-b) < EPS;
        }

        public static line segment_to_line(segment s)
        {
            line l = new line();
	        if (eq (s.x1, s.x2))
	        {
		        l.a = 1;
		        l.b = 0;
		        l.c = - s.x1;
	        }
	        else
	        {
		        l.a = - (s.y1 - s.y2) / (s.x1 - s.x2);
		        l.b = 1;
		        l.c = - (l.a * s.x1 + l.b * s.y1);
	        }
            return l;
        }
 
        public static float det (float a, float b, float c, float d)
        {
	        return a * d - b * c;
        }

        public static pt intersect(line m, line n) 
        {
            pt res = new pt();
	        float zn = det (m.a, m.b, n.a, n.b);
	        if (Math.Abs(zn) < EPS)
		        return null;
	        res.x = - det (m.c, m.b, n.c, n.b) / zn;
	        res.y = - det (m.a, m.c, n.a, n.c) / zn;
            return res;
        }
 
        public static bool parallel (line m, line n) 
        {
	        return Math.Abs(det (m.a, m.b, n.a, n.b)) < EPS;
        }
 
        public static bool equivalent (line m, line n) 
        {
            return Math.Abs(det(m.a, m.b, n.a, n.b)) < EPS
                && Math.Abs(det(m.a, m.c, n.a, n.c)) < EPS
                && Math.Abs(det(m.b, m.c, n.b, n.c)) < EPS;
        }

        public static pt segments_intersection (segment s1, segment s2)
        {
            line l1 = segment_to_line(s1);
            line l2 = segment_to_line(s2);

            pt result = intersect(l1, l2);
            if (result == null) return null;

            int x = (int)Math.Round(result.x);
            int y = (int) Math.Round(result.y);

            int x1 = 0;
            int x2 = 0;
            int x3 = 0;
            int x4 = 0;
            int y1 = 0;
            int y2 = 0;
            int y3 = 0;
            int y4 = 0;

            if ((int)s1.x1 < (int)s1.x2)
            {
                x1 = (int)s1.x1;
                x2 = (int)s1.x2;
            }
            else
            {
                x1 = (int)s1.x2;
                x2 = (int)s1.x1;
            }

            if ((int)s1.y1 < (int)s1.y2)
            {
                y1 = (int)s1.y1;
                y2 = (int)s1.y2;
            }
            else
            {
                y1 = (int)s1.y2;
                y2 = (int)s1.y1;
            }

            if ((int)s2.x1 < (int)s2.x2)
            {
                x3 = (int)s2.x1;
                x4 = (int)s2.x2;
            }
            else
            {
                x3 = (int)s2.x2;
                x4 = (int)s2.x1;
            }

            if ((int)s2.y1 < (int)s2.y2)
            {
                y3 = (int)s2.y1;
                y4 = (int)s2.y2;
            }
            else
            {
                y3 = (int)s2.y2;
                y4 = (int)s2.y1;
            }

            if(((x>=x1)&&(x<=x2)&&(x>=x3)&&(x<=x4))&&((y>=y1)&&(y<=y2)&&(y>=y3)&&(y<=y4))) 
            {
                return result;
            }
            else
	            return null;
        }
    }
}
