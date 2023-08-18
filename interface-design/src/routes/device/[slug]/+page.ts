import { error } from '@sveltejs/kit';
import type { PageLoad } from './$types';
import type { Entry } from '$lib/data.interface';

const entries = createEntries();

function createEntries(): Entry[] {
	const array = [];
	const today = new Date().getDate();

	for (let i = 0; i < today; i++) {
		const date = new Date();
		date.setDate(date.getDate() - i);

		const consumption = 2 * Math.random();
		const cost = consumption * 0.31;

		array.push({
			date: date.toLocaleDateString(),
			consumption: consumption.toFixed(2),
			cost: cost
		});
	}

	return array.sort((a, b) => {
		return new Date(a.date) > new Date(b.date) ? 0 : 1;
	});
}

export const load = (({ params }) => {
	const deviceId = Number(params.slug);
	if (params.slug === '2') {
		return {
			title: 'Connected - Mobile',
			entries: entries,
			deviceId: deviceId
		};
	}

	throw error(404, 'Not found');
}) satisfies PageLoad;
