//
//  GonaGLView.m
//  gona
//
//  Created by 胡卫君 on 16/8/29.
//  Copyright © 2016年 airgiser. All rights reserved.
//

#import <OpenGL/gl.h>
#import <string.h>
#import <wchar.h>
#import "GonaView.h"
#import "native/GnRendererFactory_mac.h"

@interface GonaView () {
    GnRenderer *m_renderer;
}
@end

@implementation GonaView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    if (!m_renderer) {
        GnGLRendererFactory rendererFactory;
        m_renderer = rendererFactory.CreateRenderer(self.frame.origin.x, self.frame.origin.y,
                                                    self.frame.size.width,self.frame.size.height);
        if (!m_renderer) {
            return;
        }
    }
    
    // style
    GnColor bkClr(120, 0, 0);
    m_renderer->clear(bkClr);
    
    GnPaint paint;
    paint.setColor(GnColor(229, 176, 69));
    paint.setLineWidth(8);
    paint.setLineCap(GnPaint::kRoundCap);
    paint.setLineJoin(GnPaint::kRoundJoin);
    paint.setTextSize(32);
    m_renderer->setPaint(paint);
    
    // Draw shapes
    const int num = 3;
    GnPoint line[num] = { GnPoint(10, 10), GnPoint(150, 100), GnPoint(250, 160) };
    m_renderer->drawPolyLine(line, num);
    
    GnPoint polygon[num] = { GnPoint(30, 150), GnPoint(160, 150), GnPoint(100, 250) };
    m_renderer->drawPolygon(polygon, num);
 
    glFlush();
}

@end
