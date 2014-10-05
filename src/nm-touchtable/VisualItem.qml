import QtQuick 2.0
import QtQuick.Particles 2.0

ParticleSystem {
    property int emitter_x: 0
    property int emitter_y: 0
    property int emitter_emitRate: 0
    property bool emitter_enabled: true

    Emitter {
        id: emitter
        objectName: "emitter"
        x: emitter_x
        y: emitter_y
        emitRate: emitter_emitRate
        width: 16
        height: 16
        lifeSpan: 5000
        size: 16
        sizeVariation: 8
        //lifeSpanVariation: 500
        //endSize: 8

        enabled: emitter_enabled

        /*
        velocity: AngleDirection {
            angle: 0
            //angleVariation: 15
            magnitude: 100
            //magnitudeVariation: 50
        }
        */

        acceleration: AngleDirection {
            angleVariation: 360;
            magnitude: 200;
            magnitudeVariation: 50

        }
        /*
        velocity: TargetDirection {
            targetItem: attractCenter
            magnitude: 100.0
            targetVariation: 100.0
        }
        */

        //velocity: PointDirection {x: root.width/10; y: root.height/10;}
        //acceleration: PointDirection {x: -root.width/40; y: -root.height/40; xVariation: -root.width/20; yVariation: -root.width/20}

        //velocity: PointDirection {xVariation: 4; yVariation: 4;}
        //acceleration: PointDirection {xVariation: 10; yVariation: 10;}
        //velocityFromMovement: 8
    }

    /*
    Attractor {
        id: attractCenter
        x: window1.width / 2
        y: window1.height / 2
        width: 16
        height: 16
        system: parent
        pointX: 0
        pointY: 0
        strength: 10.0
    }
    */



    CustomParticle {


        fragmentShader: "
            varying highp vec2 position;
            varying highp vec2 qt_TexCoord0;
            void main() {
                highp vec2 circlePos = qt_TexCoord0*2.0 - vec2(1.0,1.0);
                highp float dist = length(circlePos);
                highp float circleFactor = max(min(1.0 - dist, 1.0), 0.0);

                highp float dX = position.x / 1280.0;
                highp float dY = position.y / 800.0;

                gl_FragColor = vec4(dX, 1.0 - dX, dY, 0.0) * circleFactor;
            }"

        vertexShader: "


//            attribute highp vec2 qt_ParticlePos;
//            attribute highp vec2 qt_ParticleTex;
//            attribute highp vec4 qt_ParticleData; //  x = time,  y = lifeSpan, z = size,  w = endSize
//            attribute highp vec4 qt_ParticleVec; // x,y = constant velocity,  z,w = acceleration
//            attribute highp float qt_ParticleR;
//            uniform highp mat4 qt_Matrix;
//            uniform highp float qt_Timestamp;
//            varying highp vec2 qt_TexCoord0;

            varying highp vec2 position;

            void main() {
                //defaultMain();
                qt_TexCoord0 = qt_ParticleTex;
                highp float size = qt_ParticleData.z;
                highp float endSize = qt_ParticleData.w;
                highp float t = (qt_Timestamp - qt_ParticleData.x) / qt_ParticleData.y;
                highp float currentSize = mix(size, endSize, t * t);
                if (t < 0. || t > 1.)
                    currentSize = 0.;


                position = qt_ParticlePos
                       - currentSize / 2. + currentSize * qt_ParticleTex   // adjust size
                       + qt_ParticleVec.xy * t * qt_ParticleData.y         // apply velocity vector..
                       + 0.5 * qt_ParticleVec.zw * pow(t * qt_ParticleData.y, 2.) // apply acceleration and lifespan
                       ;

                gl_Position = qt_Matrix * vec4(position.x, position.y, 0, 1);

            }"

        /*
        fragmentShader: "
            varying highp vec2 fPos;
            varying lowp float fFade;
            varying highp vec2 qt_TexCoord0;
            void main() {//*2 because this generates dark colors mostly
                highp vec2 circlePos = qt_TexCoord0*2.0 - vec2(1.0,1.0);
                highp float dist = length(circlePos);
                highp float circleFactor = max(min(1.0 - dist, 1.0), 0.0);
                gl_FragColor = vec4(fPos.x*1.0 - fPos.y, fPos.y*2.0 - fPos.x, fPos.x*fPos.y*2.0, 0.0) * circleFactor * fFade;
            }"
            */

        /*
        vertexShader:"
            uniform lowp float qt_Opacity;
            varying lowp float fFade;
            varying highp vec2 fPos;

            void main() {
                qt_TexCoord0 = qt_ParticleTex;
                highp float size = qt_ParticleData.z;
                highp float endSize = qt_ParticleData.w;

                highp float t = (qt_Timestamp - qt_ParticleData.x) / qt_ParticleData.y;

                highp float currentSize = mix(size, endSize, t * t);

                if (t < 0. || t > 1.)
                currentSize = 0.;

                highp vec2 pos = qt_ParticlePos
                - currentSize / 2. + currentSize * qt_ParticleTex          // adjust size
                + qt_ParticleVec.xy * t * qt_ParticleData.y         // apply velocity vector..
                + 0.5 * qt_ParticleVec.zw * pow(t * qt_ParticleData.y, 2.);

                gl_Position = qt_Matrix * vec4(pos.x, pos.y, 0, 1);

                highp float fadeIn = min(t * 20., 1.);
                highp float fadeOut = 1. - max(0., min((t - 0.75) * 4., 1.));

                fFade = fadeIn * fadeOut * qt_Opacity;
                fPos = vec2(pos.x/320., pos.y/480.);
            }"
            */


    }
}
