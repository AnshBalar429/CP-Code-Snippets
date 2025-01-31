// ==UserScript==
// @name         Codeforces dark theme
// @version      1.1.2
// @description  dark theme for Codeforces
// @author       Gaurang Tandon
// @match        https://codeforces.com/*
// @match        http://codeforces.com/*
// @match        https://calendar.google.com/calendar/embed*
// @match        https://www.facebook.com/v2.8/plugins/like.php*
// @resource     desertCSS  https://raw.githubusercontent.com/GaurangTandon/codeforces-darktheme/master/desert.css
// @resource     monokaiEditorTheme https://raw.githubusercontent.com/ajaxorg/ace/62e8e9e4d3b21552dd83d454b7fd55d4981d096a/lib/ace/theme/monokai.css
// @resource     darkthemecss https://raw.githubusercontent.com/GaurangTandon/codeforces-darktheme/master/darktheme.css
// @grant        GM_addStyle
// @grant        GM_getResourceText
// @run-at       document-start
// ==/UserScript==

(function () {
	"use strict";

	var colors = {
		tableGreyRow: "#2e2e2e",
		whiteTextColor: "rgb(220, 220, 220)",
		inputBoxBackgroundBorderColor: "#383838",
		redColorJustPassesA11Y: "#ff3333",
		genericLinkBlueColor: "#4d9fef"
	};

	function overrideStyleAttribute(elm, prop, value) {
		elm.setAttribute("style", elm.getAttribute("style") + `; ${prop}: ${value} !important; `);
	}

	if (window.self != window.top && /calendar\.google\.com/.test(window.self.location.hostname)) {
		GM_addStyle(`
/* google calendar logo, see #13 */
div.logo-plus-button {
    filter: invert(1) hue-rotate(180deg);
}`);
		return;
	}

	var style = GM_getResourceText("darkthemecss"),
		desertCSS = GM_getResourceText("desertCSS");

	GM_addStyle(style);
	GM_addStyle(desertCSS);

	function applyFuncWhenElmLoaded(sel, func) {
		var elm = document.querySelectorAll(sel);
		if (!elm || elm.length == 0) return setTimeout(applyFuncWhenElmLoaded, 100, sel, func);
		for (let i = 0, len = elm.length; i < len; i++) func(elm[i]);
	}

	applyFuncWhenElmLoaded(
		"#pageContent div div h3 a, .comment-table.highlight-blue .right .ttypography p, .comment-table.highlight-blue .right .info",
		function (elm) {
			var obs = new MutationObserver(function (mutationList, observer) {
				mutationList.forEach(function (mutation) {
					if (mutation.type == "attributes" && mutation.attributeName == "style") {
						elm.setAttribute("style", elm.getAttribute("style") + "; color: white !important; ");
					}
				});
			});
			overrideStyleAttribute(elm, "color", "white");

			obs.observe(elm, { attributes: true });
		}
	);

	applyFuncWhenElmLoaded(".datatable div:nth-child(5)", function (elm) {
		elm.classList.add("dark");
	});

	applyFuncWhenElmLoaded(".unread td", function (elm) {
		elm.style.backgroundColor = "#13203a !important";
	});

	(function detect404Page() {
		applyFuncWhenElmLoaded("body > h3", function (elm) {
			if (elm.innerText.startsWith("The requested URL was not found on this server.")) {
				document.body.classList.add("notfoundpage");
			}
		});
	})();

	(function fixLavaMenu() {
		applyFuncWhenElmLoaded(".second-level-menu-list li.backLava", function (elm) {
			elm.style.backgroundImage =
				"url(https://github.com/GaurangTandon/codeforces-darktheme/raw/master/imgs/lava-right2.png)";
			elm.firstElementChild.style.backgroundImage =
				"url(https://github.com/GaurangTandon/codeforces-darktheme/raw/master/imgs/lava-left2.png)";
		});
	})();

	(function fixAceEditor() {
		applyFuncWhenElmLoaded("#editor", function (elm) {
			var monokaiEditorThemeCSS = GM_getResourceText("monokaiEditorTheme"),
				aceChromeClass = "ace-chrome";
			GM_addStyle(monokaiEditorThemeCSS);
			elm.classList.remove(aceChromeClass);
			elm.classList.add("ace-monokai");

			function checkAceClassRemoved() {
				if (elm.classList.contains(aceChromeClass)) {
					elm.classList.remove(aceChromeClass);
				}
			}
			setInterval(checkAceClassRemoved, 10);
		});
	})();

	(function fixColorRedGreenContrast() {
		if (document.readyState != "complete") {
			return setTimeout(fixColorRedGreenContrast, 100);
		}

		var elms = document.querySelectorAll("*");
		for (let i = 0, len = elms.length; i < len; i++) {
			if (getComputedStyle(elms[i]).color == "rgb(0, 128, 0)") {
				overrideStyleAttribute(elms[i], "color", "#00c700");
			}
		}

		elms = document.querySelectorAll("font");
		for (let i = 0, len = elms.length; i < len; i++) {
			if (elms[i].getAttribute("color") == "red") {
				elms[i].setAttribute("color", colors.redColorJustPassesA11Y);
			}
		}
	})();

	(function fixBlackTextInRightTableDuringContest() {
		applyFuncWhenElmLoaded(".rtable span", function (elm) {
			if (elm.style && elm.style.color == "rgb(0, 0, 0)") {
				overrideStyleAttribute(elm, "color", colors.whiteTextColor);
            }
		});
	})();

	(function improveLinkColorInGreenAlerts() {
		applyFuncWhenElmLoaded("div.alert-success a", function (elm) {
			overrideStyleAttribute(elm, "color", "#004794");
		});
	})();

	function throttleFn(fn, delayMs = 100) {
		let timeTrigger = 0, timeout = null;

		return function(...args) {
			let nowTime = Date.now();

			if (nowTime - timeTrigger >= delayMs) {
				timeTrigger = nowTime;
				fn(...args);
			} else {
				if (timeout) clearTimeout(timeout);
				let timeLeft = delayMs - (nowTime - timeTrigger);
				timeout = setTimeout(() => {
					timeout = null;
					fn(...args);
				}, timeLeft);
			}
		};
	}

	(function improveTestCaseBgColor() {
		const TEST_LINE_CLASS = "test-example-line";

		function applyBGToTestCaseLine(elm) {
			const prop = 'cssText', value = 'background-color: rgb(26, 26, 26) !important;';
			if (elm.style[prop] === '') {
				return;
			}
			if (!elm.style[prop].includes('(26') && !elm.style[prop].includes('#1a')) {
				elm.style[prop] = value;
			}
		}

		function mutationCallback(mutationList) {
			mutationList.forEach((mutation) => {
				const target = (mutation.target);
				if (target.classList.contains(TEST_LINE_CLASS)) {
					applyBGToTestCaseLine(target);
				}
			});
		}
		const observer = new MutationObserver(mutationCallback);

		applyFuncWhenElmLoaded("." + TEST_LINE_CLASS, function (elm) {
			observer.observe(document.body, { subtree: true, attributeFilter: ['style'] });
		});
	})();
})();
