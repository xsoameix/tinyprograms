function cgjsCrypt() {
    function b(a) {
        if (!a) {
            a = 8
        }
        var h = new Array(a);
        var f = [];
        for (var g = 0; g < 256; g++) {
            f[g] = g
        }
        for (g = 0; g < h.length; g++) {
            h[g] = f[Math.floor(Math.random() * f.length)]
        }
        return h
    }
    this.setDefaults = function() {
        this.params.nBits = 256;
        this.params.salt = b(8);
        this.params.salt = cgjsCryptUtil.byteArray2String(this.params.salt);
        this.params.salt = cgjsCryptUtil.convertToHex(this.params.salt);
        this.params.blockSize = 16;
        this.params.UTF8 = true;
        this.params.A0_PAD = true
    };
    this.debug = true;
    this.params = {};
    this.params.dataIn = "";
    this.params.dataOut = "";
    this.params.decryptIn = "";
    this.params.decryptOut = "";
    this.params.encryptIn = "";
    this.params.encryptOut = "";
    this.params.key = "";
    this.params.iv = "";
    this.params.clear = true;
    this.setDefaults();
    this.errors = "";
    this.warnings = "";
    this.infos = "";
    this.debugMsg = "";
    this.setParams = function(d) {
        if (!d) {
            d = {}
        }
        for (var a in d) {
            this.params[a] = d[a]
        }
    };
    this.getParams = function() {
        return this.params
    };
    this.getParam = function(a) {
        return this.params[a] || ""
    };
    this.clearParams = function() {
        this.params = {}
    };
    this.getNBits = function() {
        return this.params.nBits
    };
    this.getOutput = function() {
        return this.params.dataOut
    };
    this.setError = function(a) {
        this.error = a
    };
    this.appendError = function(a) {
        this.errors += a;
        return ""
    };
    this.getErrors = function() {
        return this.errors
    };
    this.isError = function() {
        if (this.errors.length > 0) {
            return true
        }
        return false
    };
    this.appendInfo = function(a) {
        this.infos += a;
        return ""
    };
    this.getInfos = function() {
        return this.infos
    };
    this.setDebug = function(a) {
        this.debug = a
    };
    this.appendDebug = function(a) {
        this.debugMsg += a;
        return ""
    };
    this.isDebug = function() {
        return this.debug
    };
    this.getAllMessages = function(l) {
        var i = {
            lf: "\n",
            clr_mes: false,
            verbose: 15
        };
        if (!l) {
            l = i
        }
        for (var d in i) {
            if (typeof(l[d]) == "undefined") {
                l[d] = i[d]
            }
        }
        var a = "";
        var k = "";
        for (var j in this.params) {
            switch (j) {
                case "encryptOut":
                    k = cgjsCryptUtil.toByteArray(this.params[j].toString());
                    k = cgjsCryptUtil.fragment(k.join(), 64, l.lf);
                    break;
                case "key":
                case "iv":
                    k = cgjsCryptUtil.formatHex(this.params[j], 48);
                    break;
                default:
                    k = cgjsCryptUtil.fragment(this.params[j].toString(), 64, l.lf)
            }
            a += "<p><b>" + j + "</b>:<pre>" + k + "</pre></p>"
        }
        if (this.debug) {
            a += "debug: " + this.debug + l.lf
        }
        if (this.errors.length > 0 && ((l.verbose & 1) == 1)) {
            a += "Errors:" + l.lf + this.errors + l.lf
        }
        if (this.warnings.length > 0 && ((l.verbose & 2) == 2)) {
            a += "Warnings:" + l.lf + this.warnings + l.lf
        }
        if (this.infos.length > 0 && ((l.verbose & 4) == 4)) {
            a += "Infos:" + l.lf + this.infos + l.lf
        }
        if (this.debug && ((l.verbose & 8) == 8)) {
            a += "Debug messages:" + l.lf + this.debugMsg + l.lf
        }
        if (l.clr_mes) {
            this.errors = this.infos = this.warnings = this.debug = ""
        }
        return a
    };
    this.getRandomBytes = function(a) {
        return b(a)
    }
}
cgjsCryptUtil = {};
cgjsCryptUtil.encodeBase64 = function(u, s) {
    if (!u) {
        u = ""
    }
    var B = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    s = (typeof s == "undefined") ? false : s;
    var C, E, F, c, t, x, y, A, z = [],
        D = "",
        v, e, w;
    e = s ? cgjsCryptUtil.encodeUTF8(u) : u;
    v = e.length % 3;
    if (v > 0) {
        while (v++ < 3) {
            D += "=";
            e += "\0"
        }
    }
    for (v = 0; v < e.length; v += 3) {
        C = e.charCodeAt(v);
        E = e.charCodeAt(v + 1);
        F = e.charCodeAt(v + 2);
        c = C << 16 | E << 8 | F;
        t = c >> 18 & 63;
        x = c >> 12 & 63;
        y = c >> 6 & 63;
        A = c & 63;
        z[v / 3] = B.charAt(t) + B.charAt(x) + B.charAt(y) + B.charAt(A)
    }
    w = z.join("");
    w = w.slice(0, w.length - D.length) + D;
    return w
};
cgjsCryptUtil.decodeBase64 = function(s, B) {
    if (!s) {
        s = ""
    }
    var z = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    B = (typeof B == "undefined") ? false : B;
    var A, C, D, r, v, x, y, c, w = [],
        d, t;
    t = B ? cgjsCryptUtil.decodeUTF8(s) : s;
    for (var u = 0; u < t.length; u += 4) {
        r = z.indexOf(t.charAt(u));
        v = z.indexOf(t.charAt(u + 1));
        x = z.indexOf(t.charAt(u + 2));
        y = z.indexOf(t.charAt(u + 3));
        c = r << 18 | v << 12 | x << 6 | y;
        A = c >>> 16 & 255;
        C = c >>> 8 & 255;
        D = c & 255;
        w[u / 4] = String.fromCharCode(A, C, D);
        if (y == 64) {
            w[u / 4] = String.fromCharCode(A, C)
        }
        if (x == 64) {
            w[u / 4] = String.fromCharCode(A)
        }
    }
    d = w.join("");
    d = B ? cgjsCryptUtil.decodeUTF8(d) : d;
    return d
};
cgjsCryptUtil.encodeUTF8 = function(b) {
    if (!b) {
        b = ""
    }
    b = b.replace(/[\u0080-\u07ff]/g, function(c) {
        var a = c.charCodeAt(0);
        return String.fromCharCode(192 | a >> 6, 128 | a & 63)
    });
    b = b.replace(/[\u0800-\uffff]/g, function(c) {
        var a = c.charCodeAt(0);
        return String.fromCharCode(224 | a >> 12, 128 | a >> 6 & 63, 128 | a & 63)
    });
    return b
};
cgjsCryptUtil.decodeUTF8 = function(b) {
    if (!b) {
        b = ""
    }
    b = b.replace(/[\u00c0-\u00df][\u0080-\u00bf]/g, function(c) {
        var a = (c.charCodeAt(0) & 31) << 6 | c.charCodeAt(1) & 63;
        return String.fromCharCode(a)
    });
    b = b.replace(/[\u00e0-\u00ef][\u0080-\u00bf][\u0080-\u00bf]/g, function(c) {
        var a = ((c.charCodeAt(0) & 15) << 12) | ((c.charCodeAt(1) & 63) << 6) | (c.charCodeAt(2) & 63);
        return String.fromCharCode(a)
    });
    return b
};
cgjsCryptUtil.convertToHex = function(g) {
    if (!g) {
        g = ""
    }
    var h = "";
    var f = "";
    for (var e = 0; e < g.length; e++) {
        f = g.charCodeAt(e).toString(16);
        h += (f.length == 1) ? "0" + f : f
    }
    return h
};
cgjsCryptUtil.convertFromHex = function(f) {
    if (!f) {
        f = ""
    }
    var d = "";
    for (var e = 0; e < f.length; e += 2) {
        d += String.fromCharCode(parseInt(f.substring(e, e + 2), 16))
    }
    return d
};
cgjsCryptUtil.stripLineFeeds = function(c) {
    if (!c) {
        c = ""
    }
    var d = "";
    d = c.replace(/\n/g, "");
    d = d.replace(/\r/g, "");
    return d
};
cgjsCryptUtil.toByteArray = function(d) {
    if (!d) {
        d = ""
    }
    var f = [];
    for (var e = 0; e < d.length; e++) {
        f[e] = d.charCodeAt(e)
    }
    return f
};
cgjsCryptUtil.fragment = function(h, i, g) {
    if (!h) {
        h = ""
    }
    if (!i || i >= h.length) {
        return h
    }
    if (!g) {
        g = "\n"
    }
    var j = "";
    for (var f = 0; f < h.length; f += i) {
        j += h.substr(f, i) + g
    }
    return j
};
cgjsCryptUtil.formatHex = function(i, j) {
    if (!i) {
        i = ""
    }
    if (!j) {
        j = 45
    }
    var h = "";
    var g = 0;
    var k = i.toLowerCase();
    for (var l = 0; l < k.length; l += 2) {
        h += k.substr(l, 2) + ":"
    }
    k = this.fragment(h, j);
    return k
};
cgjsCryptUtil.byteArray2String = function(b) {
    var e = "";
    for (var f = 0; f < b.length; f++) {
        e += String.fromCharCode(b[f])
    }
    return e
};

function Stream(d, c) {
    if (d instanceof Stream) {
        this.enc = d.enc;
        this.pos = d.pos
    } else {
        this.enc = d;
        this.pos = c
    }
}
Stream.prototype.parseStringHex = function(h, g) {
    if (typeof(g) == "undefined") {
        g = this.enc.length
    }
    var i = "";
    for (var f = h; f < g; ++f) {
        var j = this.get(f);
        i += this.hexDigits.charAt(j >> 4) + this.hexDigits.charAt(j & 15)
    }
    return i
};
Stream.prototype.get = function(b) {
    if (b == undefined) {
        b = this.pos++
    }
    if (b >= this.enc.length) {
        throw "Requesting byte offset " + b + " on a stream of length " + this.enc.length
    }
    return this.enc[b]
};
Stream.prototype.hexDigits = "0123456789ABCDEF";
Stream.prototype.hexDump = function(h, g) {
    var i = "";
    for (var f = h; f < g; ++f) {
        var j = this.get(f);
        i += this.hexDigits.charAt(j >> 4) + this.hexDigits.charAt(j & 15);
        if ((f & 15) == 7) {
            i += " "
        }
        i += ((f & 15) == 15) ? "\n" : " "
    }
    return i
};
Stream.prototype.parseStringISO = function(g, f) {
    var h = "";
    for (var e = g; e < f; ++e) {
        h += String.fromCharCode(this.get(e))
    }
    return h
};
Stream.prototype.parseStringUTF = function(h, g) {
    var j = "",
        i = 0;
    for (var c = h; c < g;) {
        var i = this.get(c++);
        if (i < 128) {
            j += String.fromCharCode(i)
        } else {
            if ((i > 191) && (i < 224)) {
                j += String.fromCharCode(((i & 31) << 6) | (this.get(c++) & 63))
            } else {
                j += String.fromCharCode(((i & 15) << 12) | ((this.get(c++) & 63) << 6) | (this.get(c++) & 63))
            }
        }
    }
    return j
};
Stream.prototype.reTime = /^((?:1[89]|2\d)?\d\d)(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])([01]\d|2[0-3])(?:([0-5]\d)(?:([0-5]\d)(?:[.,](\d{1,3}))?)?)?(Z|[-+](?:[0]\d|1[0-2])([0-5]\d)?)?$/;
Stream.prototype.parseTime = function(g, e) {
    var h = this.parseStringISO(g, e);
    var f = this.reTime.exec(h);
    if (!f) {
        return "Unrecognized time: " + h
    }
    h = f[1] + "-" + f[2] + "-" + f[3] + " " + f[4];
    if (f[5]) {
        h += ":" + f[5];
        if (f[6]) {
            h += ":" + f[6];
            if (f[7]) {
                h += "." + f[7]
            }
        }
    }
    if (f[8]) {
        h += " UTC";
        if (f[8] != "Z") {
            h += f[8];
            if (f[9]) {
                h += ":" + f[9]
            }
        }
    }
    return h
};
Stream.prototype.parseInteger = function(g, f) {
    if ((f - g) > 4) {
        return undefined
    }
    var h = 0;
    for (var e = g; e < f; ++e) {
        h = (h << 8) | this.get(e)
    }
    return h
};
Stream.prototype.parseOID = function(j, i) {
    var m, k = 0,
        l = 0;
    for (var n = j; n < i; ++n) {
        var h = this.get(n);
        k = (k << 7) | (h & 127);
        l += 7;
        if (!(h & 128)) {
            if (m == undefined) {
                m = parseInt(k / 40) + "." + (k % 40)
            } else {
                m += "." + ((l >= 31) ? "big" : k)
            }
            k = l = 0
        }
        m += String.fromCharCode()
    }
    return m
};
if (typeof(cgjsCrypt) != "undefined") {
    cgjsCrypt.ASN1 = function(i, h, j, g, f) {
        this.stream = i;
        this.header = h;
        this.length = j;
        this.tag = g;
        this.sub = f
    };
    cgjsCrypt.ASN1.prototype.toHexTree = function() {
        var f = {};
        f.type = this.typeName();
        if (f.type != "SEQUENCE") {
            f.value = this.stream.parseStringHex(this.posContent(), this.posEnd())
        }
        if (this.sub != null) {
            f.sub = [];
            for (var d = 0, e = this.sub.length; d < e; ++d) {
                f.sub[d] = this.sub[d].toHexTree()
            }
        }
        return f
    };
    cgjsCrypt.ASN1.prototype.typeName = function() {
        if (this.tag == undefined) {
            return "unknown"
        }
        var f = this.tag >> 6;
        var e = (this.tag >> 5) & 1;
        var d = this.tag & 31;
        switch (f) {
            case 0:
                switch (d) {
                    case 0:
                        return "EOC";
                    case 1:
                        return "BOOLEAN";
                    case 2:
                        return "INTEGER";
                    case 3:
                        return "BIT_STRING";
                    case 4:
                        return "OCTET_STRING";
                    case 5:
                        return "NULL";
                    case 6:
                        return "OBJECT_IDENTIFIER";
                    case 7:
                        return "ObjectDescriptor";
                    case 8:
                        return "EXTERNAL";
                    case 9:
                        return "REAL";
                    case 10:
                        return "ENUMERATED";
                    case 11:
                        return "EMBEDDED_PDV";
                    case 12:
                        return "UTF8String";
                    case 16:
                        return "SEQUENCE";
                    case 17:
                        return "SET";
                    case 18:
                        return "NumericString";
                    case 19:
                        return "PrintableString";
                    case 20:
                        return "TeletexString";
                    case 21:
                        return "VideotexString";
                    case 22:
                        return "IA5String";
                    case 23:
                        return "UTCTime";
                    case 24:
                        return "GeneralizedTime";
                    case 25:
                        return "GraphicString";
                    case 26:
                        return "VisibleString";
                    case 27:
                        return "GeneralString";
                    case 28:
                        return "UniversalString";
                    case 30:
                        return "BMPString";
                    default:
                        return "Universal_" + d.toString(16)
                }
            case 1:
                return "Application_" + d.toString(16);
            case 2:
                return "[" + d + "]";
            case 3:
                return "Private_" + d.toString(16)
        }
    };
    cgjsCrypt.ASN1.prototype.content = function() {
        if (this.tag == undefined) {
            return null
        }
        var g = this.tag >> 6;
        if (g != 0) {
            return null
        }
        var e = this.tag & 31;
        var h = this.posContent();
        var f = Math.abs(this.length);
        switch (e) {
            case 1:
                return (this.stream.get(h) == 0) ? "false" : "true";
            case 2:
                return this.stream.parseInteger(h, h + f);
            case 6:
                return this.stream.parseOID(h, h + f);
            case 12:
                return this.stream.parseStringUTF(h, h + f);
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 26:
                return this.stream.parseStringISO(h, h + f);
            case 23:
            case 24:
                return this.stream.parseTime(h, h + f)
        }
        return null
    };
    cgjsCrypt.ASN1.prototype.toString = function() {
        return this.typeName() + "@" + this.stream.pos + "[header:" + this.header + ",length:" + this.length + ",sub:" + ((this.sub == null) ? "null" : this.sub.length) + "]"
    };
    cgjsCrypt.ASN1.prototype.print = function(d) {
        if (d == undefined) {
            d = ""
        }
        document.writeln(d + this);
        if (this.sub != null) {
            d += "  ";
            for (var f = 0, e = this.sub.length; f < e; ++f) {
                this.sub[f].print(d)
            }
        }
    };
    cgjsCrypt.ASN1.prototype.toPrettyString = function(e) {
        if (e == undefined) {
            e = ""
        }
        var g = e + this.typeName() + " @" + this.stream.pos;
        if (this.length >= 0) {
            g += "+"
        }
        g += this.length;
        if (this.tag & 32) {
            g += " (constructed)"
        } else {
            if (((this.tag == 3) || (this.tag == 4)) && (this.sub != null)) {
                g += " (encapsulates)"
            }
        }
        g += "\n";
        if (this.sub != null) {
            e += "  ";
            for (var h = 0, f = this.sub.length; h < f; ++h) {
                g += this.sub[h].toPrettyString(e)
            }
        }
        return g
    };
    cgjsCrypt.ASN1.prototype.toDOM = function() {
        var q = document.createElement("div");
        q.className = "node";
        q.asn1 = this;
        var l = document.createElement("div");
        l.className = "head";
        var i = this.typeName();
        l.innerHTML = i;
        q.appendChild(l);
        this.head = l;
        var k = document.createElement("div");
        k.className = "value";
        i = "Offset: " + this.stream.pos + "<br/>";
        i += "Length: " + this.header + "+";
        if (this.length >= 0) {
            i += this.length
        } else {
            i += (-this.length) + " (undefined)"
        }
        if (this.tag & 32) {
            i += "<br/>(constructed)"
        } else {
            if (((this.tag == 3) || (this.tag == 4)) && (this.sub != null)) {
                i += "<br/>(encapsulates)"
            }
        }
        var n = this.content();
        if (n != null) {
            i += "<br/>Value:<br/><b>" + n + "</b>";
            if ((typeof(oids) == "object") && (this.tag == 6)) {
                var p = oids[n];
                if (p) {
                    if (p.d) {
                        i += "<br/>" + p.d
                    }
                    if (p.c) {
                        i += "<br/>" + p.c
                    }
                    if (p.w) {
                        i += "<br/>(warning!)"
                    }
                }
            }
        }
        k.innerHTML = i;
        q.appendChild(k);
        var r = document.createElement("div");
        r.className = "sub";
        if (this.sub != null) {
            for (var o = 0, m = this.sub.length; o < m; ++o) {
                r.appendChild(this.sub[o].toDOM())
            }
        }
        q.appendChild(r);
        l.switchNode = q;
        l.onclick = function() {
            var a = this.switchNode;
            a.className = (a.className == "node collapsed") ? "node" : "node collapsed"
        };
        return q
    };
    cgjsCrypt.ASN1.prototype.posStart = function() {
        return this.stream.pos
    };
    cgjsCrypt.ASN1.prototype.posContent = function() {
        return this.stream.pos + this.header
    };
    cgjsCrypt.ASN1.prototype.posEnd = function() {
        return this.stream.pos + this.header + Math.abs(this.length)
    };
    cgjsCrypt.ASN1.prototype.toHexDOM_sub = function(k, l, j, i, h) {
        if (i >= h) {
            return
        }
        var g = document.createElement("span");
        g.className = l;
        g.appendChild(document.createTextNode(j.hexDump(i, h)));
        k.appendChild(g)
    };
    cgjsCrypt.ASN1.prototype.toHexDOM = function() {
        var i = document.createElement("span");
        i.className = "hex";
        this.head.hexNode = i;
        this.head.onmouseover = function() {
            this.hexNode.className = "hexCurrent"
        };
        this.head.onmouseout = function() {
            this.hexNode.className = "hex"
        };
        this.toHexDOM_sub(i, "tag", this.stream, this.posStart(), this.posStart() + 1);
        this.toHexDOM_sub(i, (this.length >= 0) ? "dlen" : "ulen", this.stream, this.posStart() + 1, this.posContent());
        if (this.sub == null) {
            i.appendChild(document.createTextNode(this.stream.hexDump(this.posContent(), this.posEnd())))
        } else {
            if (this.sub.length > 0) {
                var h = this.sub[0];
                var j = this.sub[this.sub.length - 1];
                this.toHexDOM_sub(i, "intro", this.stream, this.posContent(), h.posStart());
                for (var f = 0, g = this.sub.length; f < g; ++f) {
                    i.appendChild(this.sub[f].toHexDOM())
                }
                this.toHexDOM_sub(i, "outro", this.stream, j.posEnd(), this.posEnd())
            }
        }
        return i
    };
    cgjsCrypt.ASN1.decodeLength = function(g) {
        var e = g.get();
        var f = e & 127;
        if (f == e) {
            return f
        }
        if (f > 3) {
            throw "Length over 24 bits not supported at position " + (g.pos - 1)
        }
        if (f == 0) {
            return -1
        }
        e = 0;
        for (var h = 0; h < f; ++h) {
            e = (e << 8) | g.get()
        }
        return e
    };
    cgjsCrypt.ASN1.hasContent = function(h, i, j) {
        if (h & 32) {
            return true
        }
        if ((h < 3) || (h > 4)) {
            return false
        }
        var k = new Stream(j);
        if (h == 3) {
            k.get()
        }
        var l = k.get();
        if ((l >> 6) & 1) {
            return false
        }
        try {
            var m = cgjsCrypt.ASN1.decodeLength(k);
            return ((k.pos - j.pos) + m == i)
        } catch (n) {
            return false
        }
    };
    cgjsCrypt.ASN1.decode = function(m) {
        if (!(m instanceof Stream)) {
            m = new Stream(m, 0)
        }
        var n = new Stream(m);
        var e = m.get();
        var p = cgjsCrypt.ASN1.decodeLength(m);
        var q = m.pos - n.pos;
        var t = null;
        if (cgjsCrypt.ASN1.hasContent(e, p, m)) {
            var s = m.pos;
            if (e == 3) {
                m.get()
            }
            t = [];
            if (p >= 0) {
                var r = s + p;
                while (m.pos < r) {
                    t[t.length] = cgjsCrypt.ASN1.decode(m)
                }
                if (m.pos != r) {
                    throw "Content size is not correct for container starting at offset " + s
                }
            } else {
                try {
                    for (;;) {
                        var l = cgjsCrypt.ASN1.decode(m);
                        if (l.tag == 0) {
                            break
                        }
                        t[t.length] = l
                    }
                    p = s - m.pos
                } catch (o) {
                    throw "Exception while decoding undefined length content: " + o
                }
            }
        } else {
            m.pos += p
        }
        return new cgjsCrypt.ASN1(n, q, p, e, t)
    };
    cgjsCrypt.ASN1.test = function() {
        var i = [{
            value: [39],
                expected: 39
        }, {
            value: [129, 201],
                expected: 201
        }, {
            value: [131, 254, 220, 186],
                expected: 16702650
        }];
        for (var l = 0, h = i.length; l < h; ++l) {
            var j = 0;
            var k = new Stream(i[l].value, 0);
            var g = cgjsCrypt.ASN1.decodeLength(k);
            if (g != i[l].expected) {
                document.write("In test[" + l + "] expected " + i[l].expected + " got " + g + "\n")
            }
        }
    }
}
var dbits;
var canary = 244837814094590;
var j_lm = ((canary & 16777215) == 15715070);

function BigInteger(b, c, a) {
    if (b != null) {
        if ("number" == typeof b) {
            this.fromNumber(b, c, a)
        } else {
            if (c == null && "string" != typeof b) {
                this.fromString(b, 256)
            } else {
                this.fromString(b, c)
            }
        }
    }
}

function nbi() {
    return new BigInteger(null)
}

function am1(l, i, c, m, j, k) {
    while (--k >= 0) {
        var n = i * this[l++] + c[m] + j;
        j = Math.floor(n / 67108864);
        c[m++] = n & 67108863
    }
    return j
}

function am2(n, h, c, s, j, v) {
    var l = h & 32767,
        i = h >> 15;
    while (--v >= 0) {
        var t = this[n] & 32767;
        var m = this[n++] >> 15;
        var u = i * t + m * l;
        t = l * t + ((u & 32767) << 15) + c[s] + (j & 1073741823);
        j = (t >>> 30) + (u >>> 15) + i * m + (j >>> 30);
        c[s++] = t & 1073741823
    }
    return j
}

function am3(n, h, c, s, j, v) {
    var l = h & 16383,
        i = h >> 14;
    while (--v >= 0) {
        var t = this[n] & 16383;
        var m = this[n++] >> 14;
        var u = i * t + m * l;
        t = l * t + ((u & 16383) << 14) + c[s] + j;
        j = (t >> 28) + (u >> 14) + i * m;
        c[s++] = t & 268435455
    }
    return j
}
if (j_lm && (navigator.appName == "Microsoft Internet Explorer")) {
    BigInteger.prototype.am = am2;
    dbits = 30
} else {
    if (j_lm && (navigator.appName != "Netscape")) {
        BigInteger.prototype.am = am1;
        dbits = 26
    } else {
        BigInteger.prototype.am = am3;
        dbits = 28
    }
}
BigInteger.prototype.DB = dbits;
BigInteger.prototype.DM = ((1 << dbits) - 1);
BigInteger.prototype.DV = (1 << dbits);
var BI_FP = 52;
BigInteger.prototype.FV = Math.pow(2, BI_FP);
BigInteger.prototype.F1 = BI_FP - dbits;
BigInteger.prototype.F2 = 2 * dbits - BI_FP;
var BI_RM = "0123456789abcdefghijklmnopqrstuvwxyz";
var BI_RC = new Array();
var rr, vv;
rr = "0".charCodeAt(0);
for (vv = 0; vv <= 9; ++vv) {
    BI_RC[rr++] = vv
}
rr = "a".charCodeAt(0);
for (vv = 10; vv < 36; ++vv) {
    BI_RC[rr++] = vv
}
rr = "A".charCodeAt(0);
for (vv = 10; vv < 36; ++vv) {
    BI_RC[rr++] = vv
}

function int2char(b) {
    return BI_RM.charAt(b)
}

function intAt(c, e) {
    var f = BI_RC[c.charCodeAt(e)];
    return (f == null) ? -1 : f
}

function bnpCopyTo(c) {
    for (var d = this.t - 1; d >= 0; --d) {
        c[d] = this[d]
    }
    c.t = this.t;
    c.s = this.s
}

function bnpFromInt(b) {
    this.t = 1;
    this.s = (b < 0) ? -1 : 0;
    if (b > 0) {
        this[0] = b
    } else {
        if (b < -1) {
            this[0] = b + DV
        } else {
            this.t = 0
        }
    }
}

function nbv(d) {
    var c = nbi();
    c.fromInt(d);
    return c
}

function bnpFromString(i, n) {
    var l;
    if (n == 16) {
        l = 4
    } else {
        if (n == 8) {
            l = 3
        } else {
            if (n == 256) {
                l = 8
            } else {
                if (n == 2) {
                    l = 1
                } else {
                    if (n == 32) {
                        l = 5
                    } else {
                        if (n == 4) {
                            l = 2
                        } else {
                            this.fromRadix(i, n);
                            return
                        }
                    }
                }
            }
        }
    }
    this.t = 0;
    this.s = 0;
    var j = i.length,
        m = false,
        k = 0;
    while (--j >= 0) {
        var b = (l == 8) ? i[j] & 255 : intAt(i, j);
        if (b < 0) {
            if (i.charAt(j) == "-") {
                m = true
            }
            continue
        }
        m = false;
        if (k == 0) {
            this[this.t++] = b
        } else {
            if (k + l > this.DB) {
                this[this.t - 1] |= (b & ((1 << (this.DB - k)) - 1)) << k;
                this[this.t++] = (b >> (this.DB - k))
            } else {
                this[this.t - 1] |= b << k
            }
        }
        k += l;
        if (k >= this.DB) {
            k -= this.DB
        }
    }
    if (l == 8 && (i[0] & 128) != 0) {
        this.s = -1;
        if (k > 0) {
            this[this.t - 1] |= ((1 << (this.DB - k)) - 1) << k
        }
    }
    this.clamp();
    if (m) {
        BigInteger.ZERO.subTo(this, this)
    }
}

function bnpClamp() {
    var b = this.s & this.DM;
    while (this.t > 0 && this[this.t - 1] == b) {
        --this.t
    }
}

function bnToString(p) {
    if (this.s < 0) {
        return "-" + this.negate().toString(p)
    }
    var o;
    if (p == 16) {
        o = 4
    } else {
        if (p == 8) {
            o = 3
        } else {
            if (p == 2) {
                o = 1
            } else {
                if (p == 32) {
                    o = 5
                } else {
                    if (p == 4) {
                        o = 2
                    } else {
                        return this.toRadix(p)
                    }
                }
            }
        }
    }
    var m = (1 << o) - 1,
        d, b = false,
        k = "",
        n = this.t;
    var i = this.DB - (n * this.DB) % o;
    if (n-- > 0) {
        if (i < this.DB && (d = this[n] >> i) > 0) {
            b = true;
            k = int2char(d)
        }
        while (n >= 0) {
            if (i < o) {
                d = (this[n] & ((1 << i) - 1)) << (o - i);
                d |= this[--n] >> (i += this.DB - o)
            } else {
                d = (this[n] >> (i -= o)) & m;
                if (i <= 0) {
                    i += this.DB;
                    --n
                }
            }
            if (d > 0) {
                b = true
            }
            if (b) {
                k += int2char(d)
            }
        }
    }
    return b ? k : "0"
}

function bnNegate() {
    var b = nbi();
    BigInteger.ZERO.subTo(this, b);
    return b
}

function bnAbs() {
    return (this.s < 0) ? this.negate() : this
}

function bnCompareTo(a) {
    var e = this.s - a.s;
    if (e != 0) {
        return e
    }
    var f = this.t;
    e = f - a.t;
    if (e != 0) {
        return e
    }
    while (--f >= 0) {
        if ((e = this[f] - a[f]) != 0) {
            return e
        }
    }
    return 0
}

function nbits(e) {
    var f = 1,
        d;
    if ((d = e >>> 16) != 0) {
        e = d;
        f += 16
    }
    if ((d = e >> 8) != 0) {
        e = d;
        f += 8
    }
    if ((d = e >> 4) != 0) {
        e = d;
        f += 4
    }
    if ((d = e >> 2) != 0) {
        e = d;
        f += 2
    }
    if ((d = e >> 1) != 0) {
        e = d;
        f += 1
    }
    return f
}

function bnBitLength() {
    if (this.t <= 0) {
        return 0
    }
    return this.DB * (this.t - 1) + nbits(this[this.t - 1] ^ (this.s & this.DM))
}

function bnpDLShiftTo(f, d) {
    var e;
    for (e = this.t - 1; e >= 0; --e) {
        d[e + f] = this[e]
    }
    for (e = f - 1; e >= 0; --e) {
        d[e] = 0
    }
    d.t = this.t + f;
    d.s = this.s
}

function bnpDRShiftTo(f, d) {
    for (var e = f; e < this.t; ++e) {
        d[e - f] = this[e]
    }
    d.t = Math.max(this.t - f, 0);
    d.s = this.s
}

function bnpLShiftTo(k, o) {
    var c = k % this.DB;
    var i = this.DB - c;
    var m = (1 << i) - 1;
    var n = Math.floor(k / this.DB),
        l = (this.s << c) & this.DM,
        p;
    for (p = this.t - 1; p >= 0; --p) {
        o[p + n + 1] = (this[p] >> i) | l;
        l = (this[p] & m) << c
    }
    for (p = n - 1; p >= 0; --p) {
        o[p] = 0
    }
    o[n] = l;
    o.t = this.t + n + 1;
    o.s = this.s;
    o.clamp()
}

function bnpRShiftTo(j, m) {
    m.s = this.s;
    var l = Math.floor(j / this.DB);
    if (l >= this.t) {
        m.t = 0;
        return
    }
    var h = j % this.DB;
    var i = this.DB - h;
    var k = (1 << h) - 1;
    m[0] = this[l] >> h;
    for (var n = l + 1; n < this.t; ++n) {
        m[n - l - 1] |= (this[n] & k) << i;
        m[n - l] = this[n] >> h
    }
    if (h > 0) {
        m[this.t - l - 1] |= (this.s & k) << i
    }
    m.t = this.t - l;
    m.clamp()
}

function bnpSubTo(j, h) {
    var i = 0,
        c = 0,
        a = Math.min(j.t, this.t);
    while (i < a) {
        c += this[i] - j[i];
        h[i++] = c & this.DM;
        c >>= this.DB
    }
    if (j.t < this.t) {
        c -= j.s;
        while (i < this.t) {
            c += this[i];
            h[i++] = c & this.DM;
            c >>= this.DB
        }
        c += this.s
    } else {
        c += this.s;
        while (i < j.t) {
            c -= j[i];
            h[i++] = c & this.DM;
            c >>= this.DB
        }
        c -= j.s
    }
    h.s = (c < 0) ? -1 : 0;
    if (c < -1) {
        h[i++] = this.DV + c
    } else {
        if (c > 0) {
            h[i++] = c
        }
    }
    h.t = i;
    h.clamp()
}

function bnpMultiplyTo(j, h) {
    var a = this.abs(),
        g = j.abs();
    var i = a.t;
    h.t = i + g.t;
    while (--i >= 0) {
        h[i] = 0
    }
    for (i = 0; i < g.t;
            ++i) {
                h[i + a.t] = a.am(0, g[i], h, i, 0, a.t)
            }
    h.s = 0;
    h.clamp();
    if (this.s != j.s) {
        BigInteger.ZERO.subTo(h, h)
    }
}

function bnpSquareTo(h) {
    var f = this.abs();
    var c = h.t = 2 * f.t;
    while (--c >= 0) {
        h[c] = 0
    }
    for (c = 0; c < f.t - 1;
            ++c) {
                var g = f.am(c, f[c], h, 2 * c, 0, 1);
                if ((h[c + f.t] += f.am(c + 1, 2 * f[c], h, 2 * c + 1, g, f.t - c - 1)) >= f.DV) {
                    h[c + f.t] -= f.DV;
                    h[c + f.t + 1] = 1
                }
            }
    if (h.t > 0) {
        h[h.t - 1] += f.am(c, f[c], h, 2 * c, 0, 1)
    }
    h.s = 0;
    h.clamp()
}

function bnpDivRemTo(C, F, G) {
    var j = C.abs();
    if (j.t <= 0) {
        return
    }
    var E = this.abs();
    if (E.t < j.t) {
        if (F != null) {
            F.fromInt(0)
        }
        if (G != null) {
            this.copyTo(G)
        }
        return
    }
    if (G == null) {
        G = nbi()
    }
    var I = nbi(),
        L = this.s,
        D = C.s;
    var m = this.DB - nbits(j[j.t - 1]);
    if (m > 0) {
        j.lShiftTo(m, I);
        E.lShiftTo(m, G)
    } else {
        j.copyTo(I);
        E.copyTo(G)
    }
    var y = I.t;
    var K = I[y - 1];
    if (K == 0) {
        return
    }
    var B = K * (1 << this.F1) + ((y > 1) ? I[y - 2] >> this.F2 : 0);
    var t = this.FV / B,
        e = (1 << this.F1) / B,
        i = 1 << this.F2;
    var q = G.t,
        r = q - y,
        H = (F == null) ? nbi() : F;
    I.dlShiftTo(r, H);
    if (G.compareTo(H) >= 0) {
        G[G.t++] = 1;
        G.subTo(H, G)
    }
    BigInteger.ONE.dlShiftTo(y, H);
    H.subTo(I, I);
    while (I.t < y) {
        I[I.t++] = 0
    }
    while (--r >= 0) {
        var J = (G[--q] == K) ? this.DM : Math.floor(G[q] * t + (G[q - 1] + i) * e);
        if ((G[q] += I.am(0, J, G, r, 0, y)) < J) {
            I.dlShiftTo(r, H);
            G.subTo(H, G);
            while (G[q] < --J) {
                G.subTo(H, G)
            }
        }
    }
    if (F != null) {
        G.drShiftTo(y, F);
        if (L != D) {
            BigInteger.ZERO.subTo(F, F)
        }
    }
    G.t = y;
    G.clamp();
    if (m > 0) {
        G.rShiftTo(m, G)
    }
    if (L < 0) {
        BigInteger.ZERO.subTo(G, G)
    }
}

function bnMod(a) {
    var d = nbi();
    this.abs().divRemTo(a, null, d);
    if (this.s < 0 && d.compareTo(BigInteger.ZERO) > 0) {
        a.subTo(d, d)
    }
    return d
}

function Classic(b) {
    this.m = b
}

function cConvert(b) {
    if (b.s < 0 || b.compareTo(this.m) >= 0) {
        return b.mod(this.m)
    } else {
        return b
    }
}

function cRevert(b) {
    return b
}

function cReduce(b) {
    b.divRemTo(this.m, null, b)
}

function cMulTo(e, f, d) {
    e.multiplyTo(f, d);
    this.reduce(d)
}

function cSqrTo(d, c) {
    d.squareTo(c);
    this.reduce(c)
}
Classic.prototype.convert = cConvert;
Classic.prototype.revert = cRevert;
Classic.prototype.reduce = cReduce;
Classic.prototype.mulTo = cMulTo;
Classic.prototype.sqrTo = cSqrTo;

function bnpInvDigit() {
    if (this.t < 1) {
        return 0
    }
    var d = this[0];
    if ((d & 1) == 0) {
        return 0
    }
    var c = d & 3;
    c = (c * (2 - (d & 15) * c)) & 15;
    c = (c * (2 - (d & 255) * c)) & 255;
    c = (c * (2 - (((d & 65535) * c) & 65535))) & 65535;
    c = (c * (2 - d * c % this.DV)) % this.DV;
    return (c > 0) ? this.DV - c : -c
}

function Montgomery(b) {
    this.m = b;
    this.mp = b.invDigit();
    this.mpl = this.mp & 32767;
    this.mph = this.mp >> 15;
    this.um = (1 << (b.DB - 15)) - 1;
    this.mt2 = 2 * b.t
}

function montConvert(d) {
    var c = nbi();
    d.abs().dlShiftTo(this.m.t, c);
    c.divRemTo(this.m, null, c);
    if (d.s < 0 && c.compareTo(BigInteger.ZERO) > 0) {
        this.m.subTo(c, c)
    }
    return c
}

function montRevert(d) {
    var c = nbi();
    d.copyTo(c);
    this.reduce(c);
    return c
}

function montReduce(f) {
    while (f.t <= this.mt2) {
        f[f.t++] = 0
    }
    for (var h = 0; h < this.m.t;
            ++h) {
                var e = f[h] & 32767;
                var g = (e * this.mpl + (((e * this.mph + (f[h] >> 15) * this.mpl) & this.um) << 15)) & f.DM;
                e = h + this.m.t;
                f[e] += this.m.am(0, g, f, h, 0, this.m.t);
                while (f[e] >= f.DV) {
                    f[e] -= f.DV;
                    f[++e] ++
                }
            }
    f.clamp();
    f.drShiftTo(this.m.t, f);
    if (f.compareTo(this.m) >= 0) {
        f.subTo(this.m, f)
    }
}

function montSqrTo(d, c) {
    d.squareTo(c);
    this.reduce(c)
}

function montMulTo(e, f, d) {
    e.multiplyTo(f, d);
    this.reduce(d)
}
Montgomery.prototype.convert = montConvert;
Montgomery.prototype.revert = montRevert;
Montgomery.prototype.reduce = montReduce;
Montgomery.prototype.mulTo = montMulTo;
Montgomery.prototype.sqrTo = montSqrTo;

function bnpIsEven() {
    return ((this.t > 0) ? (this[0] & 1) : this.s) == 0
}

function bnpExp(k, i) {
    if (k > 4294967295 || k < 1) {
        return BigInteger.ONE
    }
    var l = nbi(),
        g = nbi(),
        m = i.convert(this),
        n = nbits(k) - 1;
    m.copyTo(l);
    while (--n >= 0) {
        i.sqrTo(l, g);
        if ((k & (1 << n)) > 0) {
            i.mulTo(g, m, l)
        } else {
            var e = l;
            l = g;
            g = e
        }
    }
    return i.revert(l)
}

function bnModPowInt(d, e) {
    var f;
    if (d < 256 || e.isEven()) {
        f = new Classic(e)
    } else {
        f = new Montgomery(e)
    }
    return this.exp(d, f)
}
BigInteger.prototype.copyTo = bnpCopyTo;
BigInteger.prototype.fromInt = bnpFromInt;
BigInteger.prototype.fromString = bnpFromString;
BigInteger.prototype.clamp = bnpClamp;
BigInteger.prototype.dlShiftTo = bnpDLShiftTo;
BigInteger.prototype.drShiftTo = bnpDRShiftTo;
BigInteger.prototype.lShiftTo = bnpLShiftTo;
BigInteger.prototype.rShiftTo = bnpRShiftTo;
BigInteger.prototype.subTo = bnpSubTo;
BigInteger.prototype.multiplyTo = bnpMultiplyTo;
BigInteger.prototype.squareTo = bnpSquareTo;
BigInteger.prototype.divRemTo = bnpDivRemTo;
BigInteger.prototype.invDigit = bnpInvDigit;
BigInteger.prototype.isEven = bnpIsEven;
BigInteger.prototype.exp = bnpExp;
BigInteger.prototype.toString = bnToString;
BigInteger.prototype.negate = bnNegate;
BigInteger.prototype.abs = bnAbs;
BigInteger.prototype.compareTo = bnCompareTo;
BigInteger.prototype.bitLength = bnBitLength;
BigInteger.prototype.mod = bnMod;
BigInteger.prototype.modPowInt = bnModPowInt;
BigInteger.ZERO = nbv(0);
BigInteger.ONE = nbv(1);

function bnClone() {
    var b = nbi();
    this.copyTo(b);
    return b
}

function bnIntValue() {
    if (this.s < 0) {
        if (this.t == 1) {
            return this[0] - this.DV
        } else {
            if (this.t == 0) {
                return -1
            }
        }
    } else {
        if (this.t == 1) {
            return this[0]
        } else {
            if (this.t == 0) {
                return 0
            }
        }
    }
    return ((this[1] & ((1 << (32 - this.DB)) - 1)) << this.DB) | this[0]
}

function bnByteValue() {
    return (this.t == 0) ? this.s : (this[0] << 24) >> 24
}

function bnShortValue() {
    return (this.t == 0) ? this.s : (this[0] << 16) >> 16
}

function bnpChunkSize(b) {
    return Math.floor(Math.LN2 * this.DB / Math.log(b))
}

function bnSigNum() {
    if (this.s < 0) {
        return -1
    } else {
        if (this.t <= 0 || (this.t == 1 && this[0] <= 0)) {
            return 0
        } else {
            return 1
        }
    }
}

function bnpToRadix(n) {
    if (n == null) {
        n = 10
    }
    if (this.signum() == 0 || n < 2 || n > 36) {
        return "0"
    }
    var l = this.chunkSize(n);
    var m = Math.pow(n, l);
    var b = nbv(m),
        a = nbi(),
        d = nbi(),
        k = "";
    this.divRemTo(b, a, d);
    while (a.signum() > 0) {
        k = (m + d.intValue()).toString(n).substr(1) + k;
        a.divRemTo(b, a, d)
    }
    return d.intValue().toString(n) + k
}

function bnpFromRadix(b, j) {
    this.fromInt(0);
    if (j == null) {
        j = 10
    }
    var o = this.chunkSize(j);
    var n = Math.pow(j, o),
        p = false,
        r = 0,
        d = 0;
    for (var q = 0; q < b.length;
            ++q) {
                var i = intAt(b, q);
                if (i < 0) {
                    if (b.charAt(q) == "-" && this.signum() == 0) {
                        p = true
                    }
                    continue
                }
                d = j * d + i;
                if (++r >= o) {
                    this.dMultiply(n);
                    this.dAddOffset(d, 0);
                    r = 0;
                    d = 0
                }
            }
    if (r > 0) {
        this.dMultiply(Math.pow(j, r));
        this.dAddOffset(d, 0)
    }
    if (p) {
        BigInteger.ZERO.subTo(this, this)
    }
}

function bnpFromNumber(c, i, a) {
    if ("number" == typeof i) {
        if (c < 2) {
            this.fromInt(1)
        } else {
            this.fromNumber(c, a);
            if (!this.testBit(c - 1)) {
                this.bitwiseTo(BigInteger.ONE.shiftLeft(c - 1), op_or, this)
            }
            if (this.isEven()) {
                this.dAddOffset(1, 0)
            }
            while (!this.isProbablePrime(i)) {
                this.dAddOffset(2, 0);
                if (this.bitLength() > c) {
                    this.subTo(BigInteger.ONE.shiftLeft(c - 1), this)
                }
            }
        }
    } else {
        var j = new Array(),
            b = c & 7;
        j.length = (c >> 3) + 1;
        i.nextBytes(j);
        if (b > 0) {
            j[0] &= ((1 << b) - 1)
        } else {
            j[0] = 0
        }
        this.fromString(j, 256)
    }
}

function bnToByteArray() {
    var d = this.t,
        j = new Array();
    j[0] = this.s;
    var i = this.DB - (d * this.DB) % 8,
        h, g = 0;
    if (d-- > 0) {
        if (i < this.DB && (h = this[d] >> i) != (this.s & this.DM) >> i) {
            j[g++] = h | (this.s << (this.DB - i))
        }
        while (d >= 0) {
            if (i < 8) {
                h = (this[d] & ((1 << i) - 1)) << (8 - i);
                h |= this[--d] >> (i += this.DB - 8)
            } else {
                h = (this[d] >> (i -= 8)) & 255;
                if (i <= 0) {
                    i += this.DB;
                    --d
                }
            }
            if ((h & 128) != 0) {
                h |= -256
            }
            if (g == 0 && (this.s & 128) != (h & 128)) {
                ++g
            }
            if (g > 0 || h != this.s) {
                j[g++] = h
            }
        }
    }
    return j
}

function bnEquals(a) {
    return (this.compareTo(a) == 0)
}

function bnMin(a) {
    return (this.compareTo(a) < 0) ? this : a
}

function bnMax(a) {
    return (this.compareTo(a) > 0) ? this : a
}

function bnpBitwiseTo(l, f, j) {
    var k, i, a = Math.min(l.t, this.t);
    for (k = 0; k < a;
            ++k) {
                j[k] = f(this[k], l[k])
            }
    if (l.t < this.t) {
        i = l.s & this.DM;
        for (k = a; k < this.t;
                ++k) {
                    j[k] = f(this[k], i)
                }
        j.t = this.t
    } else {
        i = this.s & this.DM;
        for (k = a; k < l.t;
                ++k) {
                    j[k] = f(i, l[k])
                }
        j.t = l.t
    }
    j.s = f(this.s, l.s);
    j.clamp()
}

function op_and(d, c) {
    return d & c
}

function bnAnd(a) {
    var d = nbi();
    this.bitwiseTo(a, op_and, d);
    return d
}

function op_or(d, c) {
    return d | c
}

function bnOr(a) {
    var d = nbi();
    this.bitwiseTo(a, op_or, d);
    return d
}

function op_xor(d, c) {
    return d ^ c
}

function bnXor(a) {
    var d = nbi();
    this.bitwiseTo(a, op_xor, d);
    return d
}

function op_andnot(d, c) {
    return d & ~c
}

function bnAndNot(a) {
    var d = nbi();
    this.bitwiseTo(a, op_andnot, d);
    return d
}

function bnNot() {
    var c = nbi();
    for (var d = 0; d < this.t; ++d) {
        c[d] = this.DM & ~this[d]
    }
    c.t = this.t;
    c.s = ~this.s;
    return c
}

function bnShiftLeft(c) {
    var d = nbi();
    if (c < 0) {
        this.rShiftTo(-c, d)
    } else {
        this.lShiftTo(c, d)
    }
    return d
}

function bnShiftRight(c) {
    var d = nbi();
    if (c < 0) {
        this.lShiftTo(-c, d)
    } else {
        this.rShiftTo(c, d)
    }
    return d
}

function lbit(d) {
    if (d == 0) {
        return -1
    }
    var c = 0;
    if ((d & 65535) == 0) {
        d >>= 16;
        c += 16
    }
    if ((d & 255) == 0) {
        d >>= 8;
        c += 8
    }
    if ((d & 15) == 0) {
        d >>= 4;
        c += 4
    }
    if ((d & 3) == 0) {
        d >>= 2;
        c += 2
    }
    if ((d & 1) == 0) {
        ++c
    }
    return c
}

function bnGetLowestSetBit() {
    for (var b = 0; b < this.t; ++b) {
        if (this[b] != 0) {
            return b * this.DB + lbit(this[b])
        }
    }
    if (this.s < 0) {
        return this.t * this.DB
    }
    return -1
}

function cbit(d) {
    var c = 0;
    while (d != 0) {
        d &= d - 1;
        ++c
    }
    return c
}

function bnBitCount() {
    var f = 0,
        e = this.s & this.DM;
    for (var d = 0; d < this.t; ++d) {
        f += cbit(this[d] ^ e)
    }
    return f
}

function bnTestBit(c) {
    var d = Math.floor(c / this.DB);
    if (d >= this.t) {
        return (this.s != 0)
    }
    return ((this[d] & (1 << (c % this.DB))) != 0)
}

function bnpChangeBit(f, d) {
    var e = BigInteger.ONE.shiftLeft(f);
    this.bitwiseTo(e, d, e);
    return e
}

function bnSetBit(b) {
    return this.changeBit(b, op_or)
}

function bnClearBit(b) {
    return this.changeBit(b, op_andnot)
}

function bnFlipBit(b) {
    return this.changeBit(b, op_xor)
}

function bnpAddTo(j, h) {
    var i = 0,
        c = 0,
        a = Math.min(j.t, this.t);
    while (i < a) {
        c += this[i] + j[i];
        h[i++] = c & this.DM;
        c >>= this.DB
    }
    if (j.t < this.t) {
        c += j.s;
        while (i < this.t) {
            c += this[i];
            h[i++] = c & this.DM;
            c >>= this.DB
        }
        c += this.s
    } else {
        c += this.s;
        while (i < j.t) {
            c += j[i];
            h[i++] = c & this.DM;
            c >>= this.DB
        }
        c += j.s
    }
    h.s = (c < 0) ? -1 : 0;
    if (c > 0) {
        h[i++] = c
    } else {
        if (c < -1) {
            h[i++] = this.DV + c
        }
    }
    h.t = i;
    h.clamp()
}

function bnAdd(a) {
    var d = nbi();
    this.addTo(a, d);
    return d
}

function bnSubtract(a) {
    var d = nbi();
    this.subTo(a, d);
    return d
}

function bnMultiply(a) {
    var d = nbi();
    this.multiplyTo(a, d);
    return d
}

function bnDivide(a) {
    var d = nbi();
    this.divRemTo(a, d, null);
    return d
}

function bnRemainder(a) {
    var d = nbi();
    this.divRemTo(a, null, d);
    return d
}

function bnDivideAndRemainder(a) {
    var e = nbi(),
        f = nbi();
    this.divRemTo(a, e, f);
    return new Array(e, f)
}

function bnpDMultiply(b) {
    this[this.t] = this.am(0, b - 1, this, 0, 0, this.t);
    ++this.t;
    this.clamp()
}

function bnpDAddOffset(c, d) {
    while (this.t <= d) {
        this[this.t++] = 0
    }
    this[d] += c;
    while (this[d] >= this.DV) {
        this[d] -= this.DV;
        if (++d >= this.t) {
            this[this.t++] = 0
        }++this[d]
    }
}

function NullExp() {}

function nNop(b) {
    return b
}

function nMulTo(e, f, d) {
    e.multiplyTo(f, d)
}

function nSqrTo(d, c) {
    d.squareTo(c)
}
NullExp.prototype.convert = nNop;
NullExp.prototype.revert = nNop;
NullExp.prototype.mulTo = nMulTo;
NullExp.prototype.sqrTo = nSqrTo;

function bnPow(b) {
    return this.exp(b, new NullExp())
}

function bnpMultiplyLowerTo(a, g, h) {
    var i = Math.min(this.t + a.t, g);
    h.s = 0;
    h.t = i;
    while (i > 0) {
        h[--i] = 0
    }
    var j;
    for (j = h.t - this.t; i < j; ++i) {
        h[i + this.t] = this.am(0, a[i], h, i, 0, this.t)
    }
    for (j = Math.min(a.t, g); i < j; ++i) {
        this.am(0, a[i], h, i, 0, g - i)
    }
    h.clamp()
}

function bnpMultiplyUpperTo(a, f, g) {
    --f;
    var h = g.t = this.t + a.t - f;
    g.s = 0;
    while (--h >= 0) {
        g[h] = 0
    }
    for (h = Math.max(f - this.t, 0); h < a.t; ++h) {
        g[this.t + h - f] = this.am(f - h, a[h], g, 0, 0, this.t + h - f)
    }
    g.clamp();
    g.drShiftTo(1, g)
}

function Barrett(b) {
    this.r2 = nbi();
    this.q3 = nbi();
    BigInteger.ONE.dlShiftTo(2 * b.t, this.r2);
    this.mu = this.r2.divide(b);
    this.m = b
}

function barrettConvert(d) {
    if (d.s < 0 || d.t > 2 * this.m.t) {
        return d.mod(this.m)
    } else {
        if (d.compareTo(this.m) < 0) {
            return d
        } else {
            var c = nbi();
            d.copyTo(c);
            this.reduce(c);
            return c
        }
    }
}

function barrettRevert(b) {
    return b
}

function barrettReduce(b) {
    b.drShiftTo(this.m.t - 1, this.r2);
    if (b.t > this.m.t + 1) {
        b.t = this.m.t + 1;
        b.clamp()
    }
    this.mu.multiplyUpperTo(this.r2, this.m.t + 1, this.q3);
    this.m.multiplyLowerTo(this.q3, this.m.t + 1, this.r2);
    while (b.compareTo(this.r2) < 0) {
        b.dAddOffset(1, this.m.t + 1)
    }
    b.subTo(this.r2, b);
    while (b.compareTo(this.m) >= 0) {
        b.subTo(this.m, b)
    }
}

function barrettSqrTo(d, c) {
    d.squareTo(c);
    this.reduce(c)
}

function barrettMulTo(e, f, d) {
    e.multiplyTo(f, d);
    this.reduce(d)
}
Barrett.prototype.convert = barrettConvert;
Barrett.prototype.revert = barrettRevert;
Barrett.prototype.reduce = barrettReduce;
Barrett.prototype.mulTo = barrettMulTo;
Barrett.prototype.sqrTo = barrettSqrTo;

function bnModPow(e, n) {
    var j = e.bitLength(),
        m, z = nbv(1),
        D;
    if (j <= 0) {
        return z
    } else {
        if (j < 18) {
            m = 1
        } else {
            if (j < 48) {
                m = 3
            } else {
                if (j < 144) {
                    m = 4
                } else {
                    if (j < 768) {
                        m = 5
                    } else {
                        m = 6
                    }
                }
            }
        }
    }
    if (j < 8) {
        D = new Classic(n)
    } else {
        if (n.isEven()) {
            D = new Barrett(n)
        } else {
            D = new Montgomery(n)
        }
    }
    var g = new Array(),
        r = 3,
        F = m - 1,
        C = (1 << m) - 1;
    g[1] = D.convert(this);
    if (m > 1) {
        var i = nbi();
        D.sqrTo(g[1], i);
        while (r <= C) {
            g[r] = nbi();
            D.mulTo(i, g[r - 2], g[r]);
            r += 2
        }
    }
    var k = e.t - 1,
        B, E = true,
        t = nbi(),
        w;
    j = nbits(e[k]) - 1;
    while (k >= 0) {
        if (j >= F) {
            B = (e[k] >> (j - F)) & C
        } else {
            B = (e[k] & ((1 << (j + 1)) - 1)) << (F - j);
            if (k > 0) {
                B |= e[k - 1] >> (this.DB + j - F)
            }
        }
        r = m;
        while ((B & 1) == 0) {
            B >>= 1;
            --r
        }
        if ((j -= r) < 0) {
            j += this.DB;
            --k
        }
        if (E) {
            g[B].copyTo(z);
            E = false
        } else {
            while (r > 1) {
                D.sqrTo(z, t);
                D.sqrTo(t, z);
                r -= 2
            }
            if (r > 0) {
                D.sqrTo(z, t)
            } else {
                w = z;
                z = t;
                t = w
            }
            D.mulTo(t, g[B], z)
        }
        while (k >= 0 && (e[k] & (1 << j)) == 0) {
            D.sqrTo(z, t);
            w = z;
            z = t;
            t = w;
            if (--j < 0) {
                j = this.DB - 1;
                --k
            }
        }
    }
    return D.revert(z)
}

function bnGCD(l) {
    var a = (this.s < 0) ? this.negate() : this.clone();
    var g = (l.s < 0) ? l.negate() : l.clone();
    if (a.compareTo(g) < 0) {
        var j = a;
        a = g;
        g = j
    }
    var k = a.getLowestSetBit(),
        i = g.getLowestSetBit();
    if (i < 0) {
        return a
    }
    if (k < i) {
        i = k
    }
    if (i > 0) {
        a.rShiftTo(i, a);
        g.rShiftTo(i, g)
    }
    while (a.signum() > 0) {
        if ((k = a.getLowestSetBit()) > 0) {
            a.rShiftTo(k, a)
        }
        if ((k = g.getLowestSetBit()) > 0) {
            g.rShiftTo(k, g)
        }
        if (a.compareTo(g) >= 0) {
            a.subTo(g, a);
            a.rShiftTo(1, a)
        } else {
            g.subTo(a, g);
            g.rShiftTo(1, g)
        }
    }
    if (i > 0) {
        g.lShiftTo(i, g)
    }
    return g
}

function bnpModInt(g) {
    if (g <= 0) {
        return 0
    }
    var h = this.DV % g,
        d = (this.s < 0) ? g - 1 : 0;
    if (this.t > 0) {
        if (h == 0) {
            d = this[0] % g
        } else {
            for (var f = this.t - 1; f >= 0; --f) {
                d = (h * d + this[f]) % g
            }
        }
    }
    return d
}

function bnModInverse(o) {
    var c = o.isEven();
    if ((this.isEven() && c) || o.signum() == 0) {
        return BigInteger.ZERO
    }
    var d = o.clone(),
        m = this.clone();
    var n = nbv(1),
        p = nbv(0),
        a = nbv(0),
        b = nbv(1);
    while (d.signum() != 0) {
        while (d.isEven()) {
            d.rShiftTo(1, d);
            if (c) {
                if (!n.isEven() || !p.isEven()) {
                    n.addTo(this, n);
                    p.subTo(o, p)
                }
                n.rShiftTo(1, n)
            } else {
                if (!p.isEven()) {
                    p.subTo(o, p)
                }
            }
            p.rShiftTo(1, p)
        }
        while (m.isEven()) {
            m.rShiftTo(1, m);
            if (c) {
                if (!a.isEven() || !b.isEven()) {
                    a.addTo(this, a);
                    b.subTo(o, b)
                }
                a.rShiftTo(1, a)
            } else {
                if (!b.isEven()) {
                    b.subTo(o, b)
                }
            }
            b.rShiftTo(1, b)
        }
        if (d.compareTo(m) >= 0) {
            d.subTo(m, d);
            if (c) {
                n.subTo(a, n)
            }
            p.subTo(b, p)
        } else {
            m.subTo(d, m);
            if (c) {
                a.subTo(n, a)
            }
            b.subTo(p, b)
        }
    }
    if (m.compareTo(BigInteger.ONE) != 0) {
        return BigInteger.ZERO
    }
    if (b.compareTo(o) >= 0) {
        return b.subtract(o)
    }
    if (b.signum() < 0) {
        b.addTo(o, b)
    } else {
        return b
    }
    if (b.signum() < 0) {
        return b.add(o)
    } else {
        return b
    }
}
var lowprimes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509];
var lplim = (1 << 26) / lowprimes[lowprimes.length - 1];

function bnIsProbablePrime(h) {
    var i, f = this.abs();
    if (f.t == 1 && f[0] <= lowprimes[lowprimes.length - 1]) {
        for (i = 0; i < lowprimes.length;
                ++i) {
                    if (f[0] == lowprimes[i]) {
                        return true
                    }
                }
        return false
    }
    if (f.isEven()) {
        return false
    }
    i = 1;
    while (i < lowprimes.length) {
        var g = lowprimes[i],
            j = i + 1;
        while (j < lowprimes.length && g < lplim) {
            g *= lowprimes[j++]
        }
        g = f.modInt(g);
        while (i < j) {
            if (g % lowprimes[i++] == 0) {
                return false
            }
        }
    }
    return f.millerRabin(h)
}

function bnpMillerRabin(m) {
    var k = this.subtract(BigInteger.ONE);
    var p = k.getLowestSetBit();
    if (p <= 0) {
        return false
    }
    var j = k.shiftRight(p);
    m = (m + 1) >> 1;
    if (m > lowprimes.length) {
        m = lowprimes.length
    }
    var a = nbi();
    for (var n = 0; n < m; ++n) {
        a.fromInt(lowprimes[n]);
        var i = a.modPow(j, this);
        if (i.compareTo(BigInteger.ONE) != 0 && i.compareTo(k) != 0) {
            var o = 1;
            while (o++ < p && i.compareTo(k) != 0) {
                i = i.modPowInt(2, this);
                if (i.compareTo(BigInteger.ONE) == 0) {
                    return false
                }
            }
            if (i.compareTo(k) != 0) {
                return false
            }
        }
    }
    return true
}
BigInteger.prototype.chunkSize = bnpChunkSize;
BigInteger.prototype.toRadix = bnpToRadix;
BigInteger.prototype.fromRadix = bnpFromRadix;
BigInteger.prototype.fromNumber = bnpFromNumber;
BigInteger.prototype.bitwiseTo = bnpBitwiseTo;
BigInteger.prototype.changeBit = bnpChangeBit;
BigInteger.prototype.addTo = bnpAddTo;
BigInteger.prototype.dMultiply = bnpDMultiply;
BigInteger.prototype.dAddOffset = bnpDAddOffset;
BigInteger.prototype.multiplyLowerTo = bnpMultiplyLowerTo;
BigInteger.prototype.multiplyUpperTo = bnpMultiplyUpperTo;
BigInteger.prototype.modInt = bnpModInt;
BigInteger.prototype.millerRabin = bnpMillerRabin;
BigInteger.prototype.clone = bnClone;
BigInteger.prototype.intValue = bnIntValue;
BigInteger.prototype.byteValue = bnByteValue;
BigInteger.prototype.shortValue = bnShortValue;
BigInteger.prototype.signum = bnSigNum;
BigInteger.prototype.toByteArray = bnToByteArray;
BigInteger.prototype.equals = bnEquals;
BigInteger.prototype.min = bnMin;
BigInteger.prototype.max = bnMax;
BigInteger.prototype.and = bnAnd;
BigInteger.prototype.or = bnOr;
BigInteger.prototype.xor = bnXor;
BigInteger.prototype.andNot = bnAndNot;
BigInteger.prototype.not = bnNot;
BigInteger.prototype.shiftLeft = bnShiftLeft;
BigInteger.prototype.shiftRight = bnShiftRight;
BigInteger.prototype.getLowestSetBit = bnGetLowestSetBit;
BigInteger.prototype.bitCount = bnBitCount;
BigInteger.prototype.testBit = bnTestBit;
BigInteger.prototype.setBit = bnSetBit;
BigInteger.prototype.clearBit = bnClearBit;
BigInteger.prototype.flipBit = bnFlipBit;
BigInteger.prototype.add = bnAdd;
BigInteger.prototype.subtract = bnSubtract;
BigInteger.prototype.multiply = bnMultiply;
BigInteger.prototype.divide = bnDivide;
BigInteger.prototype.remainder = bnRemainder;
BigInteger.prototype.divideAndRemainder = bnDivideAndRemainder;
BigInteger.prototype.modPow = bnModPow;
BigInteger.prototype.modInverse = bnModInverse;
BigInteger.prototype.pow = bnPow;
BigInteger.prototype.gcd = bnGCD;
BigInteger.prototype.isProbablePrime = bnIsProbablePrime;

function SecureRandom() {
    this.rng_state;
    this.rng_pool;
    this.rng_pptr;
    this.rng_seed_int = function(a) {
        this.rng_pool[this.rng_pptr++] ^= a & 255;
        this.rng_pool[this.rng_pptr++] ^= (a >> 8) & 255;
        this.rng_pool[this.rng_pptr++] ^= (a >> 16) & 255;
        this.rng_pool[this.rng_pptr++] ^= (a >> 24) & 255;
        if (this.rng_pptr >= rng_psize) {
            this.rng_pptr -= rng_psize
        }
    };
    this.rng_seed_time = function() {
        this.rng_seed_int(new Date().getTime())
    };
    if (this.rng_pool == null) {
        this.rng_pool = new Array();
        this.rng_pptr = 0;
        var d;
        if (navigator.appName == "Netscape" && navigator.appVersion < "5" && window.crypto) {
            var c = window.crypto.random(32);
            for (d = 0; d < c.length;
                    ++d) {
                        this.rng_pool[this.rng_pptr++] = c.charCodeAt(d) & 255
                    }
        }
        while (this.rng_pptr < rng_psize) {
            d = Math.floor(65536 * Math.random());
            this.rng_pool[this.rng_pptr++] = d >>> 8;
            this.rng_pool[this.rng_pptr++] = d & 255
        }
        this.rng_pptr = 0;
        this.rng_seed_time()
    }
    this.rng_get_byte = function() {
        if (this.rng_state == null) {
            this.rng_seed_time();
            this.rng_state = prng_newstate();
            this.rng_state.init(this.rng_pool);
            for (this.rng_pptr = 0; this.rng_pptr < this.rng_pool.length;
                    ++this.rng_pptr) {
                        this.rng_pool[this.rng_pptr] = 0
                    }
            this.rng_pptr = 0
        }
        return this.rng_state.next()
    };
    this.nextBytes = function(a) {
        var b;
        for (b = 0; b < a.length;
                ++b) {
                    a[b] = this.rng_get_byte()
                }
    }
}

function Arcfour() {
    this.i = 0;
    this.j = 0;
    this.S = new Array()
}

function ARC4init(g) {
    var h, f, e;
    for (h = 0; h < 256;
            ++h) {
                this.S[h] = h
            }
    f = 0;
    for (h = 0; h < 256; ++h) {
        f = (f + this.S[h] + g[h % g.length]) & 255;
        e = this.S[h];
        this.S[h] = this.S[f];
        this.S[f] = e
    }
    this.i = 0;
    this.j = 0
}

function ARC4next() {
    var b;
    this.i = (this.i + 1) & 255;
    this.j = (this.j + this.S[this.i]) & 255;
    b = this.S[this.i];
    this.S[this.i] = this.S[this.j];
    this.S[this.j] = b;
    return this.S[(b + this.S[this.i]) & 255]
}
Arcfour.prototype.init = ARC4init;
Arcfour.prototype.next = ARC4next;

function prng_newstate() {
    return new Arcfour()
}
var rng_psize = 256;
if (typeof(cgjsCrypt) != "undefined" && typeof(BigInteger) != "undefined" && typeof(SecureRandom) != "undefined" && typeof(Arcfour) != "undefined") {
    function parseBigInt(c, d) {
        return new BigInteger(c, d)
    }

    function linebrk(h, g) {
        var f = "";
        var e = 0;
        while (e + g < h.length) {
            f += h.substring(e, e + g) + "\n";
            e += g
        }
        return f + h.substring(e, h.length)
    }

    function byte2Hex(b) {
        if (b < 16) {
            return "0" + b.toString(16)
        } else {
            return b.toString(16)
        }
    }

    function pkcs1unpad2(h, d) {
        var b = h.toByteArray();
        var i = 0;
        while (i < b.length && b[i] == 0) {
            ++i
        }
        if (b.length - i != d - 1 || b[i] != 2) {
            return null
        }++i;
        while (b[i] != 0) {
            if (++i >= b.length) {
                return null
            }
        }
        var j = "";
        while (++i < b.length) {
            j += String.fromCharCode(b[i])
        }
        return j
    }

    function pkcs1pad2(k, i) {
        if (i < k.length + 11) {
            throw "9900";
            return null
        }
        var j = new Array();
        var l = k.length - 1;
        while (l >= 0 && i > 0) {
            j[--i] = k.charCodeAt(l--)
        }
        j[--i] = 0;
        var g = new SecureRandom();
        var h = new Array();
        while (i > 2) {
            h[0] = 0;
            while (h[0] == 0) {
                g.nextBytes(h)
            }
            j[--i] = h[0]
        }
        j[--i] = 2;
        j[--i] = 0;
        return new BigInteger(j)
    }
    cgjsCrypt.RSA = function() {
        this.n = null;
        this.e = 0;
        this.d = null;
        this.p = null;
        this.q = null;
        this.dmp1 = null;
        this.dmq1 = null;
        this.coeff = null
    };
    cgjsCrypt.RSA.prototype.doPrivate = function(e) {
        if (this.p == null || this.q == null) {
            return e.modPow(this.d, this.n)
        }
        var f = e.mod(this.p).modPow(this.dmp1, this.p);
        var d = e.mod(this.q).modPow(this.dmq1, this.q);
        while (f.compareTo(d) < 0) {
            f = f.add(this.p)
        }
        return f.subtract(d).multiply(this.coeff).mod(this.p).multiply(this.q).add(d)
    };
    cgjsCrypt.RSA.prototype.setPublic = function(f, d, e) {
        if (typeof(e) == "undefined") {
            e = 16
        }
        if (f != null && d != null && f.length > 0 && d.length > 0) {
            this.n = parseBigInt(f, e);
            this.e = parseInt(d, e)
        } else {
            throw "9901"
        }
    };
    cgjsCrypt.RSA.prototype.doPublic = function(b) {
        return b.modPowInt(this.e, this.n)
    };
    cgjsCrypt.RSA.prototype.encryptRaw = function(h) {
        var f = pkcs1pad2(h, (this.n.bitLength() + 7) >> 3);
        if (f == null) {
            return null
        }
        var g = this.doPublic(f);
        if (g == null) {
            return null
        }
        var c = g.toString(16);
        if ((c.length & 1) == 0) {
            return c
        } else {
            return "0" + c
        }
    };
    cgjsCrypt.RSA.prototype.encrypt = function(b) {
        return this.encryptRaw(b)
    };
    cgjsCrypt.RSA.prototype.decryptRaw = function(c) {
        var f = parseBigInt(c, 16);
        var e = this.doPrivate(f);
        if (e == null) {
            return null
        }
        return pkcs1unpad2(e, (this.n.bitLength() + 7) >> 3)
    };
    cgjsCrypt.RSA.prototype.decrypt = function(c) {
        var d = this.decryptRaw(c);
        d = (d) ? cgjsCryptUtil.decodeBase64(d) : "";
        return d
    };
    cgjsCrypt.RSA.prototype.setPrivate = function(g, e, h, f) {
        if (typeof(f) == "undefined") {
            f = 16
        }
        if (g != null && e != null && g.length > 0 && e.length > 0) {
            this.n = parseBigInt(g, f);
            this.e = parseInt(e, f);
            this.d = parseBigInt(h, f)
        } else {
            throw ("9902")
        }
    };
    cgjsCrypt.RSA.prototype.setPrivateEx = function(n, j, r, o, p, k, l, q, m) {
        if (typeof(m) == "undefined") {
            m = 16
        }
        if (n != null && j != null && n.length > 0 && j.length > 0) {
            this.n = parseBigInt(n, m);
            this.e = parseInt(j, m);
            this.d = parseBigInt(r, m);
            this.p = parseBigInt(o, m);
            this.q = parseBigInt(p, m);
            this.dmp1 = parseBigInt(k, m);
            this.dmq1 = parseBigInt(l, m);
            this.coeff = parseBigInt(q, m)
        } else {
            throw ("9902")
        }
    };
    cgjsCrypt.RSA.prototype.generate = function(q, j) {
        var r = new SecureRandom();
        var m = q >> 1;
        this.e = parseInt(j, 16);
        var p = new BigInteger(j, 16);
        for (;;) {
            for (;;) {
                this.p = new BigInteger(q - m, 1, r);
                if (this.p.subtract(BigInteger.ONE).gcd(p).compareTo(BigInteger.ONE) == 0 && this.p.isProbablePrime(10)) {
                    break
                }
            }
            for (;;) {
                this.q = new BigInteger(m, 1, r);
                if (this.q.subtract(BigInteger.ONE).gcd(p).compareTo(BigInteger.ONE) == 0 && this.q.isProbablePrime(10)) {
                    break
                }
            }
            if (this.p.compareTo(this.q) <= 0) {
                var k = this.p;
                this.p = this.q;
                this.q = k
            }
            var l = this.p.subtract(BigInteger.ONE);
            var o = this.q.subtract(BigInteger.ONE);
            var n = l.multiply(o);
            if (n.gcd(p).compareTo(BigInteger.ONE) == 0) {
                this.n = this.p.multiply(this.q);
                this.d = p.modInverse(n);
                this.dmp1 = this.d.mod(l);
                this.dmq1 = this.d.mod(o);
                this.coeff = this.q.modInverse(this.p);
                break
            }
        }
    };
    cgjsCrypt.RSA.prototype.getASNData = function(g) {
        var h = {};
        var j = [];
        var i = 0;
        if (g.value && g.type == "INTEGER") {
            j[i++] = g.value
        }
        if (g.sub) {
            for (var f = 0; f < g.sub.length; f++) {
                j = j.concat(this.getASNData(g.sub[f]))
            }
        }
        return j
    };
    cgjsCrypt.RSA.prototype.setKeyFromASN = function(l, j) {
        var k = ["N", "E", "D", "P", "Q", "DP", "DQ", "C"];
        var i = {};
        var h = this.getASNData(j);
        switch (l) {
            case "Public":
            case "public":
                for (var g = 0; g < h.length; g++) {
                    i[k[g]] = h[g].toLowerCase()
                }
                this.setPublic(i.N, i.E, 16);
                break;
            case "Private":
            case "private":
                for (var g = 1; g < h.length; g++) {
                    i[k[g - 1]] = h[g].toLowerCase()
                }
                this.setPrivateEx(i.N, i.E, i.D, i.P, i.Q, i.DP, i.DQ, i.C, 16);
                break
        }
    };
    cgjsCrypt.RSA.prototype.setPublicKeyFromASN = function(b) {
        this.setKeyFromASN("public", b)
    };
    cgjsCrypt.RSA.prototype.setPrivateKeyFromASN = function(b) {
        this.setKeyFromASN("private", b)
    };
    cgjsCrypt.RSA.prototype.getParameters = function() {
        var b = {};
        if (this.n != null) {
            b.n = this.n
        }
        b.e = this.e;
        if (this.d != null) {
            b.d = this.d
        }
        if (this.p != null) {
            b.p = this.p
        }
        if (this.q != null) {
            b.q = this.q
        }
        if (this.dmp1 != null) {
            b.dmp1 = this.dmp1
        }
        if (this.dmq1 != null) {
            b.dmq1 = this.dmq1
        }
        if (this.coeff != null) {
            b.c = this.coeff
        }
        return b
    }
}

function certParser(q) {
    var i = q.split("\n");
    var v = false;
    var u = false;
    var t = false;
    var o = "";
    var s = {};
    s.info = "";
    s.salt = "";
    s.iv;
    s.b64 = "";
    s.aes = false;
    s.mode = "";
    s.bits = 0;
    for (var p = 0; p < i.length; p++) {
        o = i[p].substr(0, 9);
        if (p == 1 && o != "Proc-Type" && o.indexOf("M") == 0) {
            u = true
        }
        switch (o) {
            case "-----BEGI":
                v = true;
                break;
            case "Proc-Type":
                if (v) {
                    s.info = i[p]
                }
                break;
            case "DEK-Info:":
                           if (v) {
                               var r = i[p].split(",");
                               var m = r[0].split(": ");
                               var n = m[1].split("-");
                               s.aes = (n[0] == "AES") ? true : false;
                               s.mode = n[2];
                               s.bits = parseInt(n[1]);
                               s.salt = r[1].substr(0, 16);
                               s.iv = r[1]
                           }
                           break;
            case "":
                           if (v) {
                               u = true
                           }
                           break;
            case "-----END ":
                           if (v) {
                               u = false;
                               v = false
                           }
                           break;
            default:
                           if (v && u) {
                               s.b64 += cgjsCryptUtil.stripLineFeeds(i[p])
                           }
        }
    }
    return s
}
cgjsCrypt.CertEncrypt = function(public_key, plain_text, unused) {
    var cert = {};
    var m = "";
    var u = "";
    var cipher = "";
    params = certParser(public_key);
    if (params.b64) {
        var key = cgjsCryptUtil.decodeBase64(params.b64);
        var asn = cgjsCrypt.ASN1.decode(
                cgjsCryptUtil.toByteArray(key));
        var tree = asn.toHexTree();
        var rsa = new cgjsCrypt.RSA();
        rsa.setPublicKeyFromASN(tree);
        cipher = rsa.encrypt(plain_text);
        cipher = cgjsCryptUtil.fragment(
                cgjsCryptUtil.encodeBase64(
                    cgjsCryptUtil.convertFromHex(cipher)),
                64)
        var date = new Date();
    } else {
        throw ("9903")
    }
    return cipher
};

try {
    if (!fco08001obj.validate('1')) {
        return false;
    }
} catch (err) {
    throw err;
    return false;
}
if (document.forms['loginform']['loginform:linkCommand'].value != '') return false;
cmdLinkDisable('loginform:linkCommand', 'true');
document.forms['loginform']['loginform:linkCommand'].value = 'loginform:linkCommand';
document.forms['loginform'].submit();
return false;

(function($) {
    var klass = function() {
        this.running = false;
        this.enableHsm = true;
        this.isInit = false;
        this.timeDiff = 0;
        this.publicKey = "";
        this.init = function() {
            if (this.isInit == false) {
                var public_key = $(document.getElementById("hsmpublickey"));
                var factor = $(document.getElementById("hsmtimefactor"));
                var enable = $(document.getElementById("enableHsm"));
                if (public_key.length == 1 && factor.length == 1) {
                    if (enable.length == 1 && enable.html() != "true") {
                        this.enableHsm = false;
                        $.log("hsm enable flag: " + this.enableHsm)
                    }
                    this.publicKey = public_key.html();
                    var factor_html = factor.html();
                    var factor_date = new Date(Number(factor_html));
                    this.timeDiff = new Date().getTime() - factor_date.getTime() - 3000;
                    $.log("hsm diff: " + this.timeDiff + "  pk:" + this.publicKey);
                    this.isInit = true
                } else {
                    $.log("failed to init hsm, o1 && o2.length : " + public_key.length + "  " + factor.length)
                }
            } else {
                $.log("hsm already inited")
            }
        };
        this.timeFactor = function() {
            var c = (-480 - ((new Date()).getTimezoneOffset())) * -1 * 60 * 1000;
            var time = new Date(new Date().getTime() - this.timeDiff + c);
            var rjust = function(num) {
                return (num < 10) ? ("0" + num) : num
            };
            var time_factor =
                (time.getFullYear() + "/" +
                 rjust(time.getMonth() + 1) + "/" +
                 rjust(time.getDate()) + " " +
                 rjust(time.getHours()) + ":" +
                 rjust(time.getMinutes()) + ":" +
                 rjust(time.getSeconds()));
            $.log("timefactor: " + time_factor);
            return time_factor
        };
        this.encode = function(password_dom_id) {
            if (this.running == true) {
                return
            } else {
                this.running = true
            }
            this.init();
            try {
                if (this.enableHsm == false) {
                    return
                }
                var input = $.byId(password_dom_id);
                if (input.length == 1 &&
                    input.val().length > 0 &&
                    input.val().length < 30) {
                    var plain_text = input.val().concat(this.timeFactor());
                    var cipher = cgjsCrypt.CertEncrypt(this.publicKey, plain_text, 0);
                    input.val(input.val().length + "," + cipher)
                }
            } catch (error) {
                if (error == "9900") {
                    alert("Message too long for RSA")
                } else if (error == "9901") {
                    alert("Invalid RSA public key")
                } else if (error == "9902") {
                    alert("Invalid RSA private key")
                } else if (error == "9903") {
                    alert("Could not find public key")
                } else {
                    alert("其它錯誤: " + error)
                }
            }finally {
                this.running = false
            }
        }
    };
    $.ibhsm = function() {
        var body = $(document.body);
        var ibhsm = body.data("ibhsm");
        if (ibhsm) return ibhsm;
        var obj = new klass();
        body.data("ibhsm", obj);
        return obj;
    }
})(jQuery);
setTimeout(function() {
    $.ibhsm().init()
}, 3000);
var fco08001obj = {validate: function(a) {
    if ($("#loginform\\:showDuplicateLoginArea").val() != "accept" && $("#loginform\\:custid").val().length < 7) {
        $.ivalidator("loginform").addErr(b2cFCOpty["FCO08001.00006"]);
        $.ivalidator("loginform").showErrs(false);
        return false
    }
    if ($("#loginform\\:showDuplicateLoginArea").val() != "accept" && $("#loginform\\:name").val().length < 6) {
        $.ivalidator("loginform").addErr(b2cFCOpty["FCO08001.00007"]);
        $.ivalidator("loginform").showErrs(false);
        return false
    }
    if ($("#loginform\\:showDuplicateLoginArea").val() != "accept" && $("#loginform\\:passwd").val().length < 6) {
        $.ivalidator("loginform").addErr(b2cFCOpty["FCO08001.00008"]);
        $.ivalidator("loginform").showErrs(false);
        return false
    }
    if ($("#loginform\\:showDuplicateLoginArea").val() != "accept" && $("#loginform\\:onError").val() == "true" && $("#loginform\\:magicNumber").val().length < 5) {
        $.ivalidator("loginform").addErr(b2cFCOpty["FCO08001.00009"]);
        $.ivalidator("loginform").showErrs(false);
        return false
    }
    $.ivalidator("loginform").reset();
    $.docMask();
    $.ibhsm().encode("loginform:passwd");
    return true
},refreshCaptcha: function() {
    var b = document.getElementById("captcha");
    var a = new Date().getTime();
    var c = b.src;
    if (/[\?&]version=/.test(c)) {
        b.src = c.replace(/version=\d*/, "version=" + a)
    } else {
        b.src = c + "?version=" + a
    }
    return false
},switchMsg: function(b, c) {
    $(b).parent().siblings().removeClass("current").end().addClass("current");
    $(".ad_wrap").hide();
    var a = $("#tab" + c);
    if (a.length == 0) {
        $("#tabLogin").show()
    } else {
        a.fadeIn()
    }
    $("#loginform\\:selectedFunc").val(c);
    return false
}};
