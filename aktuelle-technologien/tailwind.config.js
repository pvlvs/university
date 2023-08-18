/** @type {import('tailwindcss').Config} */
export default {
	content: ['./src/**/*.{html,js,svelte,ts}'],
	theme: {
		extend: {
			animation: {
				'slide-out': 'slide-out ease'
			},
			keyframes: {
				'slide-out': {
					'0%': { top: '-141px' },
					'100%': { top: '0' }
				}
			}
		},
		fontFamily: {
			inter: ['inter', 'sans-serif']
		},
		colors: {
			transparent: 'transparent',
			'black-transparent': 'rgba(22, 22, 22, 0.25)',
			white: 'white',
			black: '#161616',
			green: '#3C966B',
			red: '#E371B4'
		}
	},
	plugins: []
};
