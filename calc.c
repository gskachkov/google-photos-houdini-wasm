/*
        for (var i=0; i< stops.length; i++) {
            if (stops[i]) {
                var stop = stops[i] = new ColorStop(this, stops[i]);
    
                if (stop.next) {
                    stops.splice(i+1, 0, stop.next);
                    i++;
                }
            }
            else {
                stops.splice(i, 1);
                i--;
            }
        }

        if (stops[0].color.indexOf('from') == 0) {
            from = stops[0].pos*360;
            stops.shift();
        }
        // Normalize stops
    
        // Add dummy first stop or set first stop’s position to 0 if it doesn’t have one
        if (stops[0].pos === undefined) {
            stops[0].pos = 0;
        } else if (stops[0].pos > 0) {
            var first = stops[0].clone();
            first.pos = 0;
            stops.unshift(first);
        }
    
        // Add dummy last stop or set last stop’s position to 100% if it doesn’t have one
        if (stops[stops.length - 1].pos === undefined) {
            stops[stops.length - 1].pos = 1;
        }
        else if (!repeating && stops[stops.length - 1].pos < 1) {
            var last = stops[this.stops.length - 1].clone();
            last.pos = 1;
            this.stops.push(last);
        }
    
        stops.forEach(function(stop, i) {
            if (stop.pos === undefined) {
                // Evenly space color stops with no position
                for (var j=i+1; this[j]; j++) {
                    if (this[j].pos !== undefined) {
                        stop.pos = this[i-1].pos + (this[j].pos - this[i-1].pos)/(j-i+1);
                        break;
                    }
                }
            }
            else if (i > 0) {
                // Normalize color stops whose position is smaller than the position of the stop before them
                stop.pos = Math.max(stop.pos, this[i-1].pos);
            }
        }, stops);
    
        if (repeating) {
            // Repeat color stops until >= 1
            var rStops = stops.slice();
            var lastStop = rStops[stops.length-1];
            var difference = lastStop.pos - rStops[0].pos;
    
            for (var i=0; stops[stops.length-1].pos < 1 && i<10000; i++) {
                for (var j=0; j<rStops.length; j++) {
                    var s = rStops[j].clone();
                    s.pos += (i+1)*difference;
    
                    stops.push(s);
                }
            }
        }


class ColorStop {
    constructor(gradient, stop) {
        this.gradient = gradient;

        if (stop) {
            const parts = stop.match(/^(.+?)(?:\s+([\d.]+)(%|deg|turn|grad|rad)?)?(?:\s+([\d.]+)(%|deg|turn|grad|rad)?)?\s*$/);

            this.color = this.colorToRGBA(parts[1]);

            if (parts[2]) {
                const unit = parts[3];

                if (unit == "%" || parts[2] === "0" && !unit) {
                    this.pos = parts[2]/100;
                }
                else if (unit == "turn") {
                    this.pos  = +parts[2];
                }
                else if (unit == "deg") {
                    this.pos  = parts[2] / 360;
                }
                else if (unit == "grad") {
                    this.pos  = parts[2] / 400;
                }
                else if (unit == "rad") {
                    this.pos  = parts[2] / τ;
                }
            }

            if (parts[4]) {
                this.next = new ColorStop(gradient, parts[1] + " " + parts[4] + parts[5]);
            }
        }
    }
    colorToRGBA(color) {
        if (!Array.isArray(color) && color.indexOf("from") == -1) {
	    // console.log('color-#1', color);
            if (color.indexOf("rgba") > -1) {
                var rgba = color.match(/rgba?\(([\d.]+),([\d.]+),([\d.]+)(?:,([\d.]+))?\)/);
                if (rgba) {
                    rgba.shift();
                    rgba = rgba.map(function(a) { return +a });
                    rgba[3] = isNaN(rgba[3])? 1 : rgba[3];
                }
                return rgba || [0,0,0,0];
            } else if (color.indexOf("hsla") > -1) {
               var hsla = color.match(/hsla?\(([\d.]+),([\d.]+)%,([\d.]+)%,([\d.]+)/);
               if (hsla) {
                    hsla.shift();
                    hsla = hsla.map(function(a) { return +a });
                    hsla[3] = isNaN(hsla[3])? 1 : hsla[3];
                }
	        return hslaToRgba(hsla[0], hsla[1]/100, hsla[2]/100, hsla[3]);
            }
        }
        return color;
    }
    toString() {
	    return "rgba(" + this.color.join(", ") + ") " + this.pos * 100 + "%";
    }
    clone() {
        var ret = new ColorStop(this.gradient);
        ret.color = this.color;
        ret.pos = this.pos;

        return ret;
    }
}

*/
#include <stdio.h>
#include <sys/uio.h>

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT
int main(void) {
  printf("Hello World\n");
}

/* External function that is implemented in JavaScript. */
extern void putc_js(char c);

/* Basic implementation of the writev sys call. */ 
WASM_EXPORT
size_t writev_c(int fd, const struct iovec *iov, int iovcnt) {
  size_t cnt = 0;
  for (int i = 0; i < iovcnt; i++) {
    for (int j = 0; j < iov[i].iov_len; j++) {
      putc_js(((char *)iov[i].iov_base)[j]);
    }
    cnt += iov[i].iov_len;
  }
  return cnt;
}


typedef struct stopStruct {
    int val;
    struct stopStruct* next;
    char* color;
    int pos;
} stopStruct_t;


stopStruct getNewStopStrcut(node_t * gradient, char* stop, float phi) 
{
    // stopStruct newStop = {};
    stopStruct_t * node = NULL;
    head = malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }

    head->val = 1;
    head->next = NULL;

    node.gradient = gradient;

    char[] parts = matchText(stop, "/^(.+?)(?:\s+([\d.]+)(%|deg|turn|grad|rad)?)?(?:\s+([\d.]+)(%|deg|turn|grad|rad)?)?\s*$/");
    head.color = colorToRGBA(parts[1]);

    if (parts[2] != nullptr) {
        const unit = parts[3];

        if (unit == "%" || parts[2] == "0" && !unit) {
            head.pos = parts[2]/100;
        }
        else if (unit == "turn") {
            head.pos  = +parts[2];
        }
        else if (unit == "deg") {
            head.pos  = parts[2] / 360;
        }
        else if (unit == "grad") {
            head.pos  = parts[2] / 400;
        }
        else if (unit == "rad") {
            head.pos  = parts[2] / phi;
        }
    }

    if (parts[4] != nullptr) {
        char* props = parts[1] + " " + parts[4] + parts[5];
        head.next = getNewStopStrcut(props, phi);
    }

    newStop.pos = -1;
    return newStop;
}

stopStruct cloneStrcut(stopStruct stop) 
{
    stopStruct newStopStruct = getNewStopStrcut();
    newStopStruct.color = stop.color;
    newStopStruct.pos = stop.pos;

    return newStopStruct;
}

stopStruct[] spliceStop(int index, int stopIndex, stopStruct addItem)
{
    // stopStruct[] subset = malloc((length-index)*sizeof(int)); //Where i is the place you want to start your subset. 

    //for(j = index;j < length; j++)
    //    subset[j] = originalArray[j];
    //return subset;

    for(int i = 0; i < length; i++) {

    }
    return 
}

int indexOf(char* color)
{

}

void shiftStop(stopStruct[] stops)
{

}

void unshiftStop(stopStruct[] stops, stopStruct item)
{

}

WASM_EXPORT
int calcStops(int repeating, char **charStops, int length, float phi) 
{
    int from = 0;
   
    stopStruct[] stops = matchText(stop, "(?![^(]*\))\s*/");

    for (int i = 0; i < length; i++) {
        if (stops[i] != nullptr) 
        {
            stopStruct_t * node = getNewStopStrcut(stops[i], phi);
        
            if (stop.next) {
                stops = sliceStop(i+1, 0, stop.next);
                i++;
            }
        }
        else 
        {
            // TODO: Check stop slice ???
            stops = sliceStop(i, 1);
            i--;
        }
    }

    if (indexOf(stops[0].color) == 0)
    {
        from = stops[0].pos * 360;
        shiftStop(stops);
    }

    if (stops[0].pos == -1)
    {
        stops[0].pos = 0;
    } 
    else if (stops[0].pos > 0) 
    {
        stopStruct first = cloneStrcut(stops[0]);
        first.pos = 0;
        stops.unshift(first);
    }

    for (int i = 0; i < length; i ++)
    {
        for (int j = i; j < length; j++) 
        {
            currStop = stops[i];
            if (stops[j].pos !== -1) {
                currStop.pos = stops[i-1].pos + (stops[j].pos - stops[i-1].pos)/(j-i+1);
                break;
            }
        } 
        else if (i > 0) 
        {
            stop.pos = stops[i].pos > stops[i-1].pos ? stops[i].pos : stops[i-1].pos;
        } 
    }

    // TODO: Conver as well
    /*
    if (repeating) {
        // Repeat color stops until >= 1
        var rStops = stops.slice();
        var lastStop = rStops[stops.length-1];
        var difference = lastStop.pos - rStops[0].pos;

        for (var i=0; stops[stops.length-1].pos < 1 && i<10000; i++) {
            for (var j=0; j<rStops.length; j++) {
                var s = rStops[j].clone();
                s.pos += (i+1)*difference;

                stops.push(s);
            }
        }
    }
    */
    return 10;
}
