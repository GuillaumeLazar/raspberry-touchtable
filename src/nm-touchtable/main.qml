import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Particles 2.0
import CustomImage 1.0

Window {
    id: window1
    objectName: "window"
    visible: true
    //visibility: "FullScreen"
    width: 1280
    height: 800
    color: "#FF000000"

    property int newX : -1
    property int newY : -1
    property int globalEmitRate : 40 //400

    FPSMonitor {
        id: fpsMonitor
        x: 0
        y: 0
        enabled: true
    }

    Rectangle {
        id: cursor
        objectName: "cursor"
        width: 32
        height: 32
        color: "red"
        x: window1.width / 2
        y: window1.height / 2

    }

    ParticleSystem {
        id: root
        anchors.fill: parent

        Emitter {
            id: emitter
            objectName: "emitter"
            x: window1.width / 2
            y: window1.height / 2
            width: 50
            height: 50
            emitRate: globalEmitRate //globalEmitRate
            lifeSpan: 4000 //8000
            size: 24
            sizeVariation: 16
            velocity: PointDirection {x: root.width/10; y: root.height/10;}
            acceleration: PointDirection {x: -root.width/40; y: -root.height/40; xVariation: -root.width/20; yVariation: -root.width/20}
        }


        Timer {
            interval: 25; running: false; repeat: true;
            onTriggered: {
                if (newX > 0){
                    //emitter.emitRate = globalEmitRate;
                    //emitter.x = newX;
                    //emitter.y = newY;

                    //cursor.x = newX;
                    //cursor.y = newY;
                }else{
                    //emitter.emitRate = 0;
                }
            }
        }


        CustomParticle {

            fragmentShader: "
                varying highp vec2 fPos;
                varying lowp float fFade;
                varying highp vec2 qt_TexCoord0;
                void main() {//*2 because this generates dark colors mostly
                    highp vec2 circlePos = qt_TexCoord0*2.0 - vec2(1.0,1.0);
                    highp float dist = length(circlePos);
                    highp float circleFactor = max(min(1.0 - dist, 1.0), 0.0);
                    gl_FragColor = vec4(fPos.x*2.0 - fPos.y, fPos.y*2.0 - fPos.x, fPos.x*fPos.y*2.0, 0.0) * circleFactor * fFade;
                }"

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
                }
            "

        }


        /*
        // renders a tiny image
        ImageParticle {
            source: "particle.png"
            colorVariation: 1.0
        }
        */

    }
}
